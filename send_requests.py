import requests
import datetime
from datetime import timedelta
import sys
print ("This is the name of the script: ", sys.argv[0])
mac_address = str(sys.argv[1])
time = datetime.datetime.now() + timedelta(hours=2)
post_data = {'mac_address': mac_address, 'time': time}
print(post_data)
ans = requests.post("http://10.144.68.104:5000/add_record", data=post_data)
print(ans)
print(ans.text)
