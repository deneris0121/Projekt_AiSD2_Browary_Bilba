from flask import Flask, render_template, request, jsonify,redirect, url_for, session
import json
import re
import subprocess
import os
import time

app = Flask(__name__,
            template_folder='Strona_html',      # Szablony HTML
            static_folder='Strona_html')        # Statyczne pliki (CSS, obrazy)

app.secret_key = 'tajny_klucz' 
def koloruj_czerwony(text):
    # Zamiana [1;3m ... [0m na <span style="color:red"> ... </span>
    pattern = re.compile(r'\[1;3m(.*?)\[0m')
    return pattern.sub(r'<span style="color:red">\1</span>', text)

#strona poczatkowa
@app.route('/')
def home():
    return render_template('start.html')
#wpisywanie ile pol browarow itp.
@app.route('/index')
def index():
    return render_template('index.html')
#wpisywanie ile wspolrzednych do kazdej cwiartki
@app.route('/input-cwiartki')
def input_cwiartki():
    return render_template('input-cwiartki.html')
#wpisywanie wspolrzednych dla cwiartek
@app.route('/input-cwiartki-wspol')
def input_cwiartki_wspol():
    return render_template('input-cwiartki-wspol.html')
#wpisywanie ile wspolrzednych do kazdego pola
@app.route('/ilosc_wspolrzednych_dla_kazdego_pola')
def ilosc_wspolrzednych_dla_kazdego_pola():
    return render_template('ilosc_wspolrzednych_dla_kazdego_pola.html')
#wpisywanie wspolrzednych dla pol
@app.route('/input-pole')
def input_pole():
    return render_template('input-pole.html')
#wpisywanie wspolrzednych dla browarow
@app.route('/input-browary')
def input_browary():
    return render_template('input-browary.html')
#wpisywanie wspolrzednych dla karczm
@app.route('/input-karczmy')
def input_karczmy():
    return render_template('input-karczmy.html')
#wpisywanie wspolrzednych dla skrzyzowan
@app.route('/input-skrzyzowania')
def input_skrzyzowania():
    return render_template('input-skrzyzowania.html')

#output
@app.route('/output')
def output():
    return render_template('output.html')
#archiwum
@app.route('/archive')
def archive():
    return render_template('archive.html')
#archiwum-wynik
@app.route('/archive-end')
def archive_end():
    result = session.get('result', 'Brak wyników do wyświetlenia.')
    return render_template('archive_end.html', result=result)

@app.route('/error')
def error():
    error_message = session.get('output', 'Wystąpił nieznany błąd.')
    return render_template('error.html', error_message=error_message)
@app.route('/zPliku')
def zPliku():
    return render_template('zPliku.html')

@app.route('/start_archive', methods=['GET', 'POST'])
def start_archive():
    result = None
    if request.method == 'POST':
        user_input = request.form['user_input']
        algo = request.form['algo']  # "1" lub "2"
        exe_dir = os.path.join(os.path.dirname(__file__), 'Wyszukiwarka')
        exe_path = os.path.join(exe_dir, 'wyszukiwarka.exe')

        # Uruchom program i przekaż dane użytkownika jako argument
        try:
            process = subprocess.run(
                [exe_path, algo, user_input],
                capture_output=True,
                text=True,
                check=True
            )
            result = process.stdout
        except subprocess.CalledProcessError as e:
            result = f"Błąd podczas uruchamiania programu: {e.stderr}"
        
        result =koloruj_czerwony(result)

        return render_template('archive_end.html', result=result)


@app.route('/save_data', methods=['POST'])
def save_data():
    data = request.get_json()
    
    exe_dir = os.path.join(os.path.dirname(__file__), 'Projekt bilbo-vsc', 'src')
    exe_path = os.path.join(exe_dir, 'program.exe')
    # Ścieżka docelowa zapisu pliku
    file_path = os.path.join(exe_dir, 'dane.txt')
    # Usuń stary plik jeśli istnieje
    if os.path.exists(file_path):
        os.remove(file_path)

    # Zapisz nowy plik
    with open(file_path, "w") as f:
        f.write(f"{data['pola']} {data['browary']} {data['karczmy']} {data['skrzyzowania']} {data['krawedzie']}\n")

        for x, j in zip(data['xwierzch'], data['jeczmien']):
            f.write(f"{x} {j}\n")

        for cw in data['cwiartki']:
            for x, y in cw:
                f.write(f"{x} {y} ")
            f.write("\n")

        for xp in data['xpole']:
            f.write(f"{xp}\n")

        for wsp in data['wsp_pola']:
            for x, y in wsp:
                f.write(f"{x} {y} ")
            f.write("\n")

        for b in data['browary_data']:
            f.write(" ".join(map(str, b)) + "\n")

        for k in data['karczmy_data']:
            f.write(" ".join(map(str, k)) + "\n")

        for s in data['skrzyzowania_data']:
            f.write(" ".join(map(str, s)) + "\n")

    
    # Upewnij się, że plik istnieje
    if os.path.exists(exe_path):
        try:
            result = subprocess.run([exe_path], capture_output=True, text=True, cwd=exe_dir)
            session['output'] = result.stdout
            return redirect(url_for('show_result'))
        except Exception as e:
            session['output'] = f"Błąd uruchamiania programu: {e}"
            return redirect(url_for('output'))
    else:
        session['output'] = "Nie znaleziono pliku EXE."
        return redirect(url_for('error'))
    
@app.route('/result')
def show_result():
    output_text = session.get('output', 'Brak danych do wyświetlenia.')
    return render_template('end.html', output=output_text)

@app.route('/check')
def check():
    output = session.get('output', '')
    error_map = {
        "BLAD1": "Błąd: SARUMAN ZATAKOWAŁ WIOSKE.",
        "BLAD2": "Błąd: SARUMAN ZNISZCZYŁ SHIRE.",
        "BLAD3": "Błąd: SARUMAN SPALIŁ PLONY."
    }
    for code, message in error_map.items():
        if code in output:
            session['output'] = message
            return redirect(url_for('error'))
    return redirect(url_for('show_result'))
@app.route('/upload_txt', methods=['POST'])
def upload_txt():
    filename = request.form.get('nazwaPliku')
    if not filename:
        session['output'] = "Nie podano nazwy pliku."
        return redirect(url_for('error'))

    try:
        # Ścieżki
        input_path = os.path.join(os.path.dirname(__file__), filename)
        exe_dir = os.path.join(os.path.dirname(__file__), 'Projekt bilbo-vsc', 'src')
        output_path = os.path.join(exe_dir, 'dane.txt')
        exe_path = os.path.join(exe_dir, 'program.exe')

        # Przepisz dane.txt do folderu z EXE
        with open(input_path, 'r', encoding='utf-8') as infile:
            content = infile.read()
        with open(output_path, 'w', encoding='utf-8') as outfile:
            outfile.write(content)

        # Upewnij się, że .exe istnieje
        if not os.path.exists(exe_path):
            session['output'] = "Nie znaleziono programu .exe."
            return redirect(url_for('error'))

        # Uruchom program z ustawionym katalogiem roboczym
        result = subprocess.run([exe_path], capture_output=True, text=True, cwd=exe_dir)
        #session['output'] = result.stdout if result.stdout else "Program nie zwrócił żadnego wyniku."
        output = result.stdout.strip()
        print(f"=== DEBUG OUTPUT ===\n{repr(output)}")
        error_map = {
            "BLAD1": "Błąd: SARUMAN ZATAKOWAŁ WIOSKE.",
            "BLAD2": "Błąd: SARUMAN ZNISZCZYŁ SHIRE.",
            "BLAD3": "Błąd: SARUMAN SPALIŁ PLONY."
        }

       
        for code, message in error_map.items():
            if code in output:
                session['output'] = message
                return redirect(url_for('error'))

        # Jeśli nie znaleziono błędu – traktuj jako poprawne wykonanie
        session['output'] = output if output else "Program nie zwrócił żadnego wyniku."
        return redirect(url_for('show_result'))
        
    except Exception as e:
        session['output'] = f"Błąd: {e}"

    return redirect(url_for('show_result'))
def needs_recompile(exe_path, cpp_paths):
    if not os.path.exists(exe_path):
        return True
    exe_mtime = os.path.getmtime(exe_path)
    for cpp in cpp_paths:
        if os.path.getmtime(cpp) > exe_mtime:
            return True
    return False
if __name__ == '__main__':
    # Ścieżki do pliku źródłowego i wynikowego .exe
    src_dir = os.path.join(os.path.dirname(__file__), 'Projekt bilbo-vsc', 'src')
    cpp_files = [
        "main.cpp", "Calosc.cpp", "Browar.cpp", "Cwiartka.cpp",
        "FordFulkerson.cpp", "Graf.cpp", "Karczma.cpp", "Krawedz.cpp",
        "Merge_sort.cpp", "Pole.cpp", "Wezel.cpp", "Drukuj.cpp","Dekoder.cpp" ,"Huffman.cpp"
    ]
    cpp_paths = [os.path.join(src_dir, f) for f in cpp_files]
    exe_file = os.path.join(src_dir, 'program.exe')

    # ścieżki do pliku z archiwum .exe
    src_dir_arch = os.path.join(os.path.dirname(__file__), 'Wyszukiwarka')
    cpp_files_arch = [
        "main.cpp", "BoyerMoore.cpp", "KnuthMorrisPratt.cpp", 
        "Interface.cpp", "Dekoder.cpp"
    ]
    cpp_paths_arch = [os.path.join(src_dir_arch, f) for f in cpp_files_arch]
    exe_file_arch = os.path.join(src_dir_arch, 'wyszukiwarka.exe')

    
    if needs_recompile(exe_file, cpp_paths):
        print("Kompiluję program główny...")
        compile_result = subprocess.run(
            ['g++'] + cpp_paths + ['-o', exe_file],
            capture_output=True,
            text=True
        )
        if compile_result.returncode != 0:
            print("Błąd kompilacji:")
            print(compile_result.stderr)
        else:
            print("Kompilacja zakończona sukcesem.")
    if needs_recompile(exe_file_arch, cpp_paths_arch):
        print("Kompiluję wyszukiwarkę...")
        compile_result_arch = subprocess.run(
            ['g++'] + cpp_paths_arch + ['-o', exe_file_arch],
            capture_output=True,
            text=True
        )
        if compile_result_arch.returncode != 0:
            print("Błąd kompilacji:")
            print(compile_result_arch.stderr)
        else:
            print("Kompilacja zakończona sukcesem.")
    # Start Flaska
    app.run(debug=True)
