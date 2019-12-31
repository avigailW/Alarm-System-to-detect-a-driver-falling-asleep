import requests
import datetime
from datetime import timedelta


def get_mac():
    mac_address = "00.99.77.66"
    time = datetime.datetime.now() + timedelta(hours=2)
    post_data = {'mac_address': mac_address, 'time': time}
    print(post_data)
    ans = requests.post("http://10.144.68.104:5000/add_record", data=post_data)
    print(ans)
    print(ans.text)
    return mac_address


get_mac()
