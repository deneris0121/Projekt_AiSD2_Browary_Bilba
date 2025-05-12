from flask import Flask, render_template, request, jsonify,redirect, url_for, session
import json
import subprocess
import os

app = Flask(__name__,
            template_folder='Strona_html',      # Szablony HTML
            static_folder='Strona_html')        # Statyczne pliki (CSS, obrazy)

app.secret_key = 'tajny_klucz' 
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


@app.route('/error')
def error():
    return render_template('error.html')
@app.route('/zPliku')
def zPliku():
    return render_template('zPliku.html')

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
        return redirect(url_for('show_result'))
    
@app.route('/result')
def show_result():
    # Pobierz wynik z sesji i przekaż go do szablonu
    output_text = session.get('output', 'Brak danych do wyświetlenia.')
    return render_template('end.html', output=output_text)

@app.route('/upload_txt', methods=['POST'])
def upload_txt():
    filename = request.form.get('nazwaPliku')
    if not filename:
        session['output'] = "Nie podano nazwy pliku."
        return redirect(url_for('show_result'))

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
            return redirect(url_for('show_result'))

        # Uruchom program z ustawionym katalogiem roboczym
        result = subprocess.run([exe_path], capture_output=True, text=True, cwd=exe_dir)
        session['output'] = result.stdout if result.stdout else "Program nie zwrócił żadnego wyniku."

    except Exception as e:
        session['output'] = f"Błąd: {e}"

    return redirect(url_for('show_result'))
if __name__ == '__main__':
    app.run(debug=True)
