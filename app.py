from flask import Flask, render_template
import json

app = Flask(__name__,
            template_folder='Strona_html',      # Szablony HTML
            static_folder='Strona_html')        # Statyczne pliki (CSS, obrazy)
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
#end
@app.route('/end')
def end():
    return render_template('end.html')
#output
@app.route('/output')
def output():
    return render_template('output.html')
#archiwum
@app.route('/archive')
def archive():
    return render_template('archive.html')

if __name__ == '__main__':
    app.run(debug=True)
