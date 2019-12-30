from flask import Flask
from flask_mongoengine import MongoEngine
import mongoengine as me
from datetime import timedelta
import datetime

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello, World! TeamUP'


app.config['MONGODB_SETTINGS'] = {
    "db": "keepUp",
}
db = MongoEngine(app)


class DataDriversSleeping(me.EmbeddedDocument):
    times = me.ListField()


class Drivers(me.Document):
    mac = me.StringField()
    ID = me.StringField()
    name = me.StringField()
    date_birth = me.DateField()
    data_drivers_sleeping = me.EmbeddedDocumentField(DataDriversSleeping)


class DrivesSleepingTime(me.Document):
    date = me.DateField()
    drivers = me.ListField()


def add_driver(mac, id, name, date_birth):
    driver = Drivers(mac=mac, ID=id, name=name, date_birth=date_birth)
    driver.data_drivers_sleeping = DataDriversSleeping(times=[])
    driver.save()
    print(driver)


def add_sleep_time(mac, time_of_sleep):
    driver_sleeping = Drivers.objects(mac=mac).get()
    driver_sleeping.data_drivers_sleeping.times.append(time_of_sleep)
    driver_sleeping.save()


def get_times_sleeping_for_driver():
    list_of_drivers_sleeping = []
    for driver in Drivers.objects:
        list_of_drivers_sleeping.append([driver.name, len(driver.data_drivers_sleeping.times)])
    return list_of_drivers_sleeping


def get_sleep_by_hour():
    list_of_hour = []
    for i in range(24):
        list_of_hour.append(0)
    for driver in Drivers.objects:
        for time_of_sleep in driver.data_drivers_sleeping.times:
            hour = time_of_sleep.hour
            list_of_hour[int(hour)] += 1
    return list_of_hour


def get_sleep_by_day():
    list_of_day = []
    for i in range(7):
        list_of_day.append(0)
    for driver in Drivers.objects:
        for time_of_sleep in driver.data_drivers_sleeping.times:
            day = ((time_of_sleep.weekday() + 1) % 7)
            list_of_day[day] += 1
    return list_of_day


add_driver("DC:A6:32:4D:75:C5", "123456789", "Moshe Cohen", datetime.datetime(1980, 12, 5))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 29, 0))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 29, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 29, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 28, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 28, 0) + timedelta(hours=2))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 22, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 22, 0) + timedelta(hours=4))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 30, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:32:4D:75:C5", datetime.datetime(2019, 12, 30, 0) + timedelta(hours=3))

add_driver("DC:A6:32:4D:75:C1", "456123789", "Simon Avivi", datetime.datetime(1985, 8, 11))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 22, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 22, 0) + timedelta(hours=2))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 15, 0) + timedelta(hours=2))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 15, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 15, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 10, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 10, 0) + timedelta(hours=4))
add_sleep_time("DC:A6:32:4D:75:C1", datetime.datetime(2019, 12, 11, 0) + timedelta(hours=5))

add_driver("DC:A6:32:4D:75:C8", "987654321", "David Levi", datetime.datetime(1990, 4, 30))
add_sleep_time("DC:A6:32:4D:75:C8", datetime.datetime(2019, 12, 11, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:32:4D:75:C8", datetime.datetime(2019, 12, 12, 0) + timedelta(hours=2))
add_sleep_time("DC:A6:32:4D:75:C8", datetime.datetime(2019, 12, 15, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:32:4D:75:C8", datetime.datetime(2019, 12, 13, 0) + timedelta(hours=4))
add_sleep_time("DC:A6:32:4D:75:C8", datetime.datetime(2019, 12, 12, 0) + timedelta(hours=5))
add_sleep_time("DC:A6:32:4D:75:C8", datetime.datetime(2019, 12, 13, 0) + timedelta(hours=6))

add_driver("DC:A6:35:4D:75:C11", "147852369", "Shay Bash", datetime.datetime(1997, 1, 26))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 14, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 14, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 14, 0) + timedelta(hours=1))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 9, 0) + timedelta(hours=2))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 9, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 9, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 12, 0) + timedelta(hours=3))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 15, 0) + timedelta(hours=4))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 12, 0) + timedelta(hours=5))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 11, 0) + timedelta(hours=4))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 10, 0) + timedelta(hours=6))
add_sleep_time("DC:A6:35:4D:75:C11", datetime.datetime(2019, 12, 15, 0) + timedelta(hours=6))

# print(get_times_sleeping_for_driver())
#
# print(get_sleep_by_hour())

# print(get_sleep_by_day())
