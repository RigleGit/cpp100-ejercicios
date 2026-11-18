#!/usr/bin/env python3
"""Compila cada ejercicio con avisos estrictos y sanitizers y comprueba sus casos.

Cada carpeta ejercicios/NNN contiene main.cpp (y, si hace falta, más .cpp/.hpp)
y casos.json. Si existe pruebas.cpp, se compila con los .cpp que no son main.cpp
y debe terminar con estado 0.
"""
import argparse
import json
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[1]
CXX = os.environ.get("CXX", "c++")
FLAGS = ["-std=c++20", "-Wall", "-Wextra", "-Wpedantic", "-Werror", "-g",
         "-pthread", "-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
TIMEOUT = 20
ENV = dict(os.environ, ASAN_OPTIONS="detect_leaks=0:abort_on_error=0",
           UBSAN_OPTIONS="halt_on_error=1:print_stacktrace=1", LC_ALL="C.UTF-8")


def fail(msg):
    print("FALLO:", msg)
    return 1


def safe(name):
    path = PurePosixPath(name)
    if path.is_absolute() or ".." in path.parts or not path.parts:
        raise SystemExit(f"Ruta no permitida en casos: {name}")
    return path


def build(folder, out, sources):
    cmd = [CXX, *FLAGS, "-I", str(folder), *map(str, sources), "-o", str(out)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode:
        print(res.stderr)
        return False
    return True


def check_format(folders):
    if not shutil.which("clang-format"):
        print("Aviso: clang-format no está instalado; se omite el formato.")
        return 0
    files = [p for f in folders for p in sorted(f.rglob("*")) if p.suffix in {".cpp", ".hpp"}]
    if not files:
        return 0
    res = subprocess.run(["clang-format", "--dry-run", "-Werror",
                          f"--style=file:{ROOT / '.clang-format'}", *map(str, files)],
                         capture_output=True, text=True)
    if res.returncode:
        print(res.stderr[:4000])
        return fail("formato: ejecuta clang-format -i sobre los archivos indicados")
    return 0


def run_exercise(folder, tmp):
    number = folder.name
    errors = 0
    cases_file = folder / "casos.json"
    if not cases_file.is_file():
        return fail(f"{number}: falta casos.json")
    cases = json.loads(cases_file.read_text(encoding="utf-8"))
    if not cases:
        return fail(f"{number}: casos.json vacío")
    sources = sorted(p for p in folder.rglob("*.cpp") if p.name != "pruebas.cpp")
    binary = tmp / f"ej{number}"
    if not build(folder, binary, sources):
        return fail(f"{number}: no compila")
    tests = folder / "pruebas.cpp"
    if tests.is_file():
        tbin = tmp / f"pr{number}"
        others = [p for p in sources if p.name != "main.cpp"]
        if not build(folder, tbin, [tests, *others]):
            return fail(f"{number}: pruebas.cpp no compila")
        res = subprocess.run([str(tbin)], capture_output=True, text=True, timeout=TIMEOUT, env=ENV)
        if res.returncode:
            errors += fail(f"{number}: pruebas.cpp terminó con {res.returncode}\n{res.stdout}{res.stderr}")
    for i, case in enumerate(cases):
        label = f"{number} / {case.get('name', i)}"
        work = tmp / f"w{number}-{i}"
        work.mkdir()
        for name, content in case.get("files", {}).items():
            p = work / safe(name)
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(content, encoding="utf-8", newline="")
        try:
            res = subprocess.run([str(binary), *case.get("args", [])], cwd=work,
                                 input=case.get("stdin", ""), capture_output=True,
                                 text=True, timeout=TIMEOUT, env=ENV)
        except subprocess.TimeoutExpired:
            errors += fail(f"{label}: tiempo agotado")
            continue
        if "runtime error" in res.stderr or "AddressSanitizer" in res.stderr:
            errors += fail(f"{label}: sanitizer\n{res.stderr[:2000]}")
            continue
        if res.returncode != case.get("status", 0):
            errors += fail(f"{label}: estado {res.returncode}, esperado {case.get('status', 0)}\n{res.stderr}")
        if res.stdout != case.get("stdout", ""):
            errors += fail(f"{label}: stdout distinto\n--- esperado\n{case.get('stdout', '')!r}\n--- obtenido\n{res.stdout!r}")
        if "stderr" in case and res.stderr != case["stderr"]:
            errors += fail(f"{label}: stderr distinto\n--- esperado\n{case['stderr']!r}\n--- obtenido\n{res.stderr!r}")
        if "stderr_contains" in case and case["stderr_contains"] not in res.stderr:
            errors += fail(f"{label}: stderr no contiene {case['stderr_contains']!r}: {res.stderr!r}")
        for name, content in case.get("expect_files", {}).items():
            p = work / safe(name)
            if not p.is_file():
                errors += fail(f"{label}: falta el archivo {name}")
            elif p.read_bytes() != content.encode("utf-8"):
                errors += fail(f"{label}: contenido distinto en {name}: {p.read_bytes()!r}")
    return errors


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("exercises", nargs="*", help="Números como 001 o rangos 001-008.")
    args = parser.parse_args()
    folders = sorted(p for p in (ROOT / "ejercicios").iterdir() if p.is_dir())
    if args.exercises:
        wanted = set()
        for item in args.exercises:
            a, _, b = item.partition("-")
            wanted.update(f"{n:03}" for n in range(int(a), int(b or a) + 1))
        folders = [f for f in folders if f.name in wanted]
    if not folders:
        raise SystemExit("No hay ejercicios que comprobar.")
    errors = check_format(folders)
    total = 0
    with tempfile.TemporaryDirectory(prefix="cpp100-") as tmp:
        for folder in folders:
            n = len(json.loads((folder / "casos.json").read_text(encoding="utf-8"))) if (folder / "casos.json").is_file() else 0
            e = run_exercise(folder, Path(tmp))
            errors += e
            total += n
            print(f"{folder.name}: {'ok' if not e else 'FALLA'} ({n} casos)")
    print(f"{len(folders)} ejercicios, {total} casos, {errors} fallos")
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
