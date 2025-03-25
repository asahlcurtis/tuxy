# getsysinfo.py
import os
import psutil
import distro

def returninfo():
    print("CPU Cores:", psutil.cpu_count(logical=False))
    print(" CPU Threads:", psutil.cpu_count(logical=True))
    print(" CPU Usage %:", psutil.cpu_percent(interval=1))
    print(" RAM Total (MB):", psutil.virtual_memory().total / 1024 / 1024)
    print(" User:", os.getlogin())

    try:
        print("Linux Distro:", distro.name(), distro.version())
    except Exception as e:
        print("Linux Distro: Error occurred. Are you on Linux?", e)

def writeinfotofile():
    try:
        with open("sysinfo.txt", "x") as file:
            file.write(f"CPU Cores: {psutil.cpu_count(logical=False)}\n")
            file.write(f" CPU Threads: {psutil.cpu_count(logical=True)}\n")
            file.write(f" CPU Usage %: {psutil.cpu_percent(interval=1)}\n")
            file.write(f" User: {os.getlogin()}\n")
    except FileExistsError:
        with open("sysinfo.txt", "a") as file:  # If file already exists, append to it
            file.write(f"CPU Cores: {psutil.cpu_count(logical=False)}\n")
            file.write(f" CPU Threads: {psutil.cpu_count(logical=True)}\n")
            file.write(f" CPU Usage %: {psutil.cpu_percent(interval=1)}\n")
            file.write(f" User: {os.getlogin()}\n")
            file.write(f" ", distro.name(), " ", distro.version(), "\n")

returninfo()
writeinfotofile()

