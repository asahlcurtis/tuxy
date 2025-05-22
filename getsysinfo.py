import os
import psutil
import distro

def returninfo():
    """Prints system information."""
    print("CPU Cores:", psutil.cpu_count(logical=False))
    print("CPU Threads:", psutil.cpu_count(logical=True))
    print("CPU Usage %:", psutil.cpu_percent(interval=1))
    print("RAM Total (MB):", psutil.virtual_memory().total / 1024 / 1024)
    print("User:", os.getlogin())

    try:
        print("Linux Distro:", distro.name(), distro.version())
    except Exception as e:
        print("Linux Distro: Error occurred. Are you on Linux?", e)

def writeinfotofile():
    """Writes system information to sysinfo.txt."""
    try:
        # Using "w" to overwrite the file, in case it exists
        with open("sysinfo.txt", "w") as file:
            file.write(f"CPU Cores: {psutil.cpu_count(logical=False)}\n")
            file.write(f"CPU Threads: {psutil.cpu_count(logical=True)}\n")
            file.write(f"CPU Usage %: {psutil.cpu_percent(interval=1)}\n")
            file.write(f"User: {os.getlogin()}\n")
            try:
                file.write(f"{distro.name()} {distro.version()}\n")
            except Exception as e:
                file.write(f"Linux Distro: Error occurred. Are you on Linux? {e}\n")
    except FileExistsError:
        # In case the file exists and can't be created, we append to it
        with open("sysinfo.txt", "a") as file:
            file.write(f"CPU Cores: {psutil.cpu_count(logical=False)}\n")
            file.write(f"CPU Threads: {psutil.cpu_count(logical=True)}\n")
            file.write(f"CPU Usage %: {psutil.cpu_percent(interval=1)}\n")
            file.write(f"User: {os.getlogin()}\n")
            try:
                file.write(f"{distro.name()} {distro.version()}\n")
            except Exception as e:
                file.write(f"Linux Distro: Error occurred. Are you on Linux? {e}\n")

returninfo()  # Display system information in terminal
writeinfotofile()  # Write system information to sysinfo.txt
