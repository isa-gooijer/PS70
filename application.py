## test

# From CS50 and medium.com:
# part 1: https://medium.com/@anupbhande/create-a-static-website-on-github-using-python-and-flask-framework-part-1-e26c0d39bec2
# part 2: https://medium.com/@anupbhande/create-a-static-website-on-github-using-python-and-flask-part-2-335d6df42def

# Import relevant libraries
# *** Need to the delete the irrelevant ones ***

import sys, os

from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# to get the date and time for the transactions.
from datetime import datetime

# Configure application
app = Flask(__name__) # URL Routing — Home Page

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# *** MIGHT HAVE TO CHANGE THIS?! ***
# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


# Homepage
@app.route("/")
def index():
    return “Hello World!”

# Main Function, Runs at http://0.0.0.0:8000
if __name__ == “__main__”:
 app.run(port=8000)```

"""
def index():
    # get the homepage of the website.
    return render_template("index.html")"""

"""
# About
@app.route("/about")
def about():
    # get about page
    return render_template("index.html")

# 01_intro
@app.route("/intro")
def intro():
    return render_template("/assignment/01_intro.html")


# ERROR HANDLERs
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
    """