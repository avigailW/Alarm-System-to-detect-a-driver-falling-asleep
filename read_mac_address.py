
def get_mac():
    with open ("lsOutput.log", 'r') as get_mac:
        for line in get_mac:
            if "ether" in line:
                mac_address = line.split()[1].strip()
                with open("mac_address.txt", 'w') as save_mac_address:
                    save_mac_address.write(mac_address)
                # print(mac_address)
                # return mac_address

get_mac()