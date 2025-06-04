import subprocess
import shutil
import os
from urllib.request import urlretrieve
from urllib import error

default_cwd = os.getcwd()

def run_git(command):
    """
    Runs a git command.
    """
    try:
        subprocess.run(["git"] + command.split())
    except:
        print("Error: git is not available")
        exit(1)

def get_repo(origin, repo_path, commit):
    """
    Clones a git repository.
    """
    # clear repo folder if it is not empty
    repo_dir = os.listdir(repo_path)
    if len(repo_dir) > 0:
        shutil.rmtree(repo_path)
        os.mkdir(repo_path)

    run_git(f"clone {origin} {repo_path}")
    os.chdir(repo_path)
    run_git(f"checkout {commit}")
    os.chdir(default_cwd)

def download_file(url, file_path):
    """
    Downloads a file from 'url' to the 'file_path'.
    """
    try:
        urlretrieve(url, file_path)
    except error.URLError as url_error:
        print(f"Error during file downloading. Reason: {url_error.reason}")
        exit(1)

##############
# cocos2d-x
##############
print("Getting cocos2d-x...", end="")
get_repo("https://github.com/cocos2d/cocos2d-x.git", "./cpp/cocos2d", "90f6542")
# no submodule update needed, so just run download-deps.py
subprocess.run(["python", "./cpp/cocos2d/download-deps.py"])
print("OK")

##############
# other 3rd party libs
##############
print("Getting jl_signal...", end="")
get_repo("https://github.com/jeffomatic/jl_signal.git", "./cpp/third_party/jl_signal", "4c15aed")
print("OK")
print("Getting rapidjson...", end="")
get_repo("https://github.com/Tencent/rapidjson.git", "./cpp/third_party/rapidjson", "232389d")
print("OK")

##############
# Config files
##############
print("Replacing config files...", end="")
shutil.copyfile("./cpp/to_replace/cocos2d/cocos/base/ccConfig.h", "./cpp/cocos2d/cocos/base/ccConfig.h")
shutil.copyfile("./cpp/to_replace/cocos2d/cocos/CMakeLists.txt", "./cpp/cocos2d/cocos/CMakeLists.txt")
print("OK")

##############
# Roboto font
##############
print("Downloading Roboto font...", end="")
download_file(
    "https://raw.githubusercontent.com/googlefonts/roboto-2/refs/heads/main/src/hinted/Roboto-Regular.ttf",
    "./cpp/Resources/Roboto-Regular.ttf"
)
print("OK")

##############
# Setup finished
##############
print("\nSetup was finished successfully")
# wait for user's confirmation before the exit
input("\nPress Enter to exit...")
