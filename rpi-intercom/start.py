import os
from colorama import init, Fore, Back, Style
import sys
import subprocess
import webbrowser
import json
init()

sys_version = "1.0"
sys_version_code = 1
vnc_path = ""
ssh_path = ""
telnet_path = ""
vnc_port = ""
ssh_port = ""
telnet_port = ""
web_port = ""
settings_port = ""
default_raspap_ip_gateway = ""
connection_type = ""
target_user = ""
ps_prefix = Fore.WHITE + "[" + Fore.YELLOW + "INTERCOM" + Fore.WHITE + "]" + Style.RESET_ALL
print(ps_prefix + Fore.WHITE + " Starting up..." + Style.RESET_ALL)
list_prefix_star = Fore.GREEN + "[" + Fore.CYAN + "*" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_null = Fore.GREEN + "[" + Fore.CYAN + "0" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_one = Fore.GREEN + "[" + Fore.CYAN + "1" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_two = Fore.GREEN + "[" + Fore.CYAN + "2" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_three = Fore.GREEN + "[" + Fore.CYAN + "3" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_four = Fore.GREEN + "[" + Fore.CYAN + "4" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_five = Fore.GREEN + "[" + Fore.CYAN + "5" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_six = Fore.GREEN + "[" + Fore.CYAN + "6" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_seven = Fore.GREEN + "[" + Fore.CYAN + "7" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_eight = Fore.GREEN + "[" + Fore.CYAN + "8" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_nine = Fore.GREEN + "[" + Fore.CYAN + "9" + Fore.GREEN + "]" + Style.RESET_ALL
list_prefix_ten = Fore.GREEN + "[" + Fore.CYAN + "10" + Fore.GREEN + "]" + Style.RESET_ALL
current_path = str(os.path.dirname(os.path.abspath(__file__))) + "\settings.json"

os.system("title INTERCOM v" + str(sys_version))
print(ps_prefix + Fore.WHITE + " Loading settings from " + Fore.MAGENTA + current_path + Fore.WHITE + " ..." +Style.RESET_ALL)

try:
    settings = open("settings.json", "r")
except:
    print(ps_prefix + Fore.RED + " Loading settings failed" + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Unable to read settings file: Inaccessible or not found" + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Please place your settings file to " + Fore.MAGENTA + current_path + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Program closed with exit code 1" + Style.RESET_ALL)
    sys.exit(1)

if settings.mode == "r":
    read_settings = settings.read().replace("\\", "\\\\")
    try:
        settings_dict = json.loads(read_settings)
        vnc_path = settings_dict['vnc_path']
        ssh_path = settings_dict['ssh_path']
        telnet_path = settings_dict['telnet_path']
        vnc_port = settings_dict['vnc_port']
        ssh_port = settings_dict['ssh_port']
        telnet_port = settings_dict['telnet_port']
        web_port = settings_dict['web_port']
        settings_port = settings_dict['settings_port']
        default_raspap_ip_gateway = settings_dict['default_raspap_ip_gateway']
        connection_type = settings_dict['connection_type']
        target_user = settings_dict['target_user']
    except:
        print(ps_prefix + Fore.RED + " Loading settings failed" + Style.RESET_ALL)
        print(ps_prefix + Fore.RED + " Unable to read settings file: Configuration file corrupted and contains errors" + Style.RESET_ALL)
        print(ps_prefix + Fore.RED + " Program closed with exit code 1" + Style.RESET_ALL)
        sys.exit(1)
else:
    print(ps_prefix + Fore.RED + " Loading settings failed" + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Permission denied!" + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Please check if you have permissions to read files" + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Program closed with exit code 1" + Style.RESET_ALL)
    sys.exit(1)

# print(vnc_path) # DEBUG

def about(server_address):
    print(ps_prefix + Fore.WHITE + " Version: " + str(sys_version) + ", developer: Teslasoft, site: https://jarvis.studio" + Style.RESET_ALL)
    print(ps_prefix + Fore.WHITE + " Press any key to continue" + Style.RESET_ALL)
    os.system("pause >nul")
    menu(server_address)

def about2():
    print(ps_prefix + Fore.WHITE + " Version: " + str(sys_version) + ", developer: Teslasoft, site: https://jarvis.studio" + Style.RESET_ALL)
    print(ps_prefix + Fore.WHITE + " Press any key to continue" + Style.RESET_ALL)
    os.system("pause >nul")
    main()

def executor(server_address):
    pass # Implement

def command_line(server_address):
    server = server_address + ":" + web_port
    command = input(server_address + "> ")
    # ...
    if command.lower() == "help":
        print(ps_prefix + Fore.WHITE + " List of commands:" + Style.RESET_ALL)
    elif command.lower() == "exit":
        restart(server_address)
    # ... elif command == 
    else:
        print(ps_prefix + Fore.WHITE + " " + server_address + ": " + Fore.RED + "Unknown command" + Style.RESET_ALL)

def restart(server_address):
    print(ps_prefix + Fore.GREEN + " Session closed. Would you like to open main menu (Y/N)?" + Style.RESET_ALL)
    yn = input("Enter selection: ")
    if yn.lower() == "y" or yn.lower() == "yes":
        menu(server_address)
    elif yn.lower() == "n" or yn.lower() == "no":
        exit_program()
    else:
        print(ps_prefix + Fore.RED + " Please enter a correct option" + Style.RESET_ALL)
        restart(server_address)

def exit_program():
    print(ps_prefix + Fore.RED + " Program closed by user (exit code 0)" + Style.RESET_ALL)
    sys.exit(0)

def ssh_connect(server_address):
    print(ps_prefix + Fore.GREEN + " Connecting to " + Fore.MAGENTA + str(server_address) + Fore.GREEN + " with username " + Fore.MAGENTA + str(target_user) + Fore.GREEN + " via ssh with port " + Fore.RED + ssh_port + Fore.GREEN + "..." + Style.RESET_ALL)
    ssh_command = "ssh " + target_user + "@" + server_address
    os.system(ssh_command)
    print("\n" + ps_prefix + Fore.RED + " Connection with " + Fore.MAGENTA + str(server_address) + Fore.RED + " closed" + Style.RESET_ALL)
    restart(server_address)

def telnet_connect(server_address):
    print(ps_prefix + Fore.GREEN + " Connecting to " + Fore.MAGENTA + str(server_address) + Fore.GREEN + " via telnet with port " + Fore.RED + telnet_port + Fore.GREEN + "..." + Style.RESET_ALL)
    telnet_command = "telnet " + server_address
    os.system(telnet_command)
    print("\n" + ps_prefix + Fore.RED + " Connection with " + Fore.MAGENTA + str(server_address) + Fore.RED + " closed" + Style.RESET_ALL)
    restart(server_address)

def vnc_connect(server_address):
    print(ps_prefix + Fore.GREEN + " Connecting to " + Fore.MAGENTA + str(server_address) + Fore.GREEN + " via vnc with port " + Fore.RED + vnc_port + Fore.GREEN + "..." + Style.RESET_ALL)
    print(ps_prefix + Fore.GREEN + " Vnc connected successfully" + Style.RESET_ALL)
    subprocess.call([vnc_path, server_address + ":" + vnc_port])
    print("\n" + ps_prefix + Fore.RED + " Connection with " + Fore.MAGENTA + str(server_address) + Fore.RED + " closed" + Style.RESET_ALL)
    restart(server_address)

def server_info(server_address):
    print(ps_prefix + Fore.GREEN + " Opening server settings for " + Fore.MAGENTA + str(server_address) + Fore.GREEN + "..." + Style.RESET_ALL)
    url = "http://" + server_address + ":" + settings_port
    webbrowser.open(url)
    restart(server_address)

def server_selector():
    server_address = input("Please enter address to connect: ")
    print(ps_prefix + Fore.GREEN + " Selected address is " + Fore.MAGENTA + str(server_address) + Style.RESET_ALL)
    return server_address

def menu(server_address):
    print(ps_prefix + Fore.GREEN + " Please select an option" + Style.RESET_ALL)
    print(" " + Style.RESET_ALL)
    print("    " + list_prefix_one + Fore.WHITE + " Connect via ssh" + Style.RESET_ALL)
    print("    " + list_prefix_two + Fore.WHITE + " Connect via telnet" + Style.RESET_ALL)
    print("    " + list_prefix_three + Fore.WHITE + " Connect via vnc" + Style.RESET_ALL)
    print("    " + list_prefix_four + Fore.WHITE + " Server info and settings" + Style.RESET_ALL)
    print("    " + list_prefix_five + Fore.WHITE + " Server command line" + Style.RESET_ALL)
    print("    " + list_prefix_six + Fore.WHITE + " Chose another server" + Style.RESET_ALL)
    print("    " + list_prefix_seven + Fore.WHITE + " Exit program" + Style.RESET_ALL)
    print("    " + list_prefix_eight + Fore.WHITE + " Go back" + Style.RESET_ALL)
    print(" " + Style.RESET_ALL)
    choose = input("Input your choice: ")
    if str(choose) == "1":
        ssh_connect(server_address)
    elif str(choose) == "2":
        telnet_connect(server_address)
    elif str(choose) == "3":
        vnc_connect(server_address)
    elif str(choose) == "4":
        server_info(server_address)
    elif str(choose) == "5":
        print(ps_prefix + Fore.GREEN + " Connecting to " + Fore.MAGENTA + str(server_address) + Fore.GREEN + " via web console with port " + Fore.RED + web_port + Fore.GREEN + "..." + Style.RESET_ALL)
        command_line(server_address)
    elif str(choose) == "6":
        menu(server_selector())
    elif str(choose) == "7":
        exit_program()
    elif str(choose) == "8":
        main()
    else:
        print(ps_prefix + Fore.RED + " Please enter a correct option" + Style.RESET_ALL)
        menu(server_address)

def new_connection():
    print(ps_prefix + Fore.GREEN + " Please specify server address to continue" + Style.RESET_ALL)
    server_address = input("Server address: ")
    print(ps_prefix + Fore.GREEN + " Selected address is " + Fore.MAGENTA + str(server_address) + Style.RESET_ALL)
    menu(server_address)

def main():
    print(ps_prefix + Fore.WHITE + " Version " + str(sys_version) + Style.RESET_ALL)
    print(ps_prefix + Fore.GREEN + " Please select an option" + Style.RESET_ALL)
    print(" " + Style.RESET_ALL)
    print("    " + list_prefix_one + Fore.WHITE + " Connect to a server" + Style.RESET_ALL)
    print("    " + list_prefix_two + Fore.WHITE + " Program settings" + Style.RESET_ALL)
    print("    " + list_prefix_three + Fore.WHITE + " About Intercom" + Style.RESET_ALL)
    print("    " + list_prefix_four + Fore.WHITE + " Exit program" + Style.RESET_ALL)
    print(" " + Style.RESET_ALL)
    choose = input("Input your choice: ")
    if str(choose) == "1":
        new_connection()
    elif str(choose) == "2":
        pass
    elif str(choose) == "3":
        about2()
    elif str(choose) == "4":
        exit_program()

try:
    main()
except KeyboardInterrupt:
    print("\n" + ps_prefix + Fore.RED + " KeyboardInterruptException handled" + Style.RESET_ALL)
    print(ps_prefix + Fore.RED + " Program closed with exit code 1" + Style.RESET_ALL)
    sys.exit(1)
