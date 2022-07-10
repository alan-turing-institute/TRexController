import os
import sys
from flask import Flask, request, render_template
import requests

BASE_URL = os.environ["TREX_URL"] if "TREX_URL" in os.environ \
    else "http://localhost:4444"

app = Flask(__name__)

@app.route('/', methods=["GET","POST"])
def home():
    if request.method == "POST":
        if "open_jaw" in request.form:
            r = requests.post(BASE_URL+"/jaw/open")
            print("opening ", file=sys.stderr)
        elif "close_jaw" in request.form:
            r = requests.post(BASE_URL+"/jaw/close")
            print("closing ", file=sys.stderr)
    return render_template("index.html")


if __name__ == "__main__":
    app.run(host='0.0.0.0',port=5000, debug=True)
