from flask import Flask, render_template
import json

app = Flask(__name__,
            template_folder='Strona_html',      # Szablony HTML
            static_folder='Strona_html')        # Statyczne pliki (CSS, obrazy)

@app.route('/')
def home():
    return render_template('start.html')

if __name__ == '__main__':
    app.run(debug=True)
