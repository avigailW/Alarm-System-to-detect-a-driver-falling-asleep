import datetime
from keep_up_db import add_sleep_time, get_sleep_by_day, get_times_sleeping_for_driver, get_sleep_by_hour
from flask import Flask
from flask import render_template, request, redirect, url_for, jsonify, make_response, flash, abort, send_file
from flask_wtf import form
import requests
import time
import json

app = Flask(__name__)


# the home page.
@app.route('/')
def home():
    return render_template("home.html")


@app.route('/login')
def login():
    return render_template("login.html")


@app.route('/about')
def about():
    return render_template("about.html")


@app.route('/logout')
def logout():
    return render_template("login.html")


@app.route('/register')
def register():
    return render_template("register.html")


@app.route('/dashboard')
def dashboard():
    drivers = get_times_sleeping_for_driver()
    days = get_sleep_by_day()
    hours = get_sleep_by_hour()
    print("drivers   ",drivers)
    print("days   ",days)
    print("hours   ", hours)
    return render_template("dashboard.html", drivers=drivers, days=days, hours=hours)


@app.route('/add_record', methods=['GET', 'POST'])
def add_record():
    if request.method == 'POST':
        mac_address = request.form.get('mac_address')
        time_str = request.form.get('time')
        time_obj = datetime.datetime.strptime(time_str, '%Y-%m-%d %H:%M:%S.%f')
        print(type(time))
        print(mac_address, time_str)
        add_sleep_time(mac_address, time_obj)
        return f"{mac_address} at {time_str}"
    return"hello world"


if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0")
