import subprocess
import sys
import shutil
import os

default_cwd = os.getcwd()

def run_git(command):
    try:
        subprocess.run(['git'] + command.split())
    except:
        print('Error: git is not available')
        sys.exit(1)


def get_repo(name, origin, repo_path, commit):
    print('--- Getting ' + name + ' repo:')

    # clear repo folder if it is not empty
    repo_dir = os.listdir(repo_path)
    if len(repo_dir) > 0:
        shutil.rmtree(repo_path)
        os.mkdir(repo_path)

    run_git('clone ' + origin + ' ' + repo_path)
    os.chdir(repo_path)
    run_git('checkout ' + commit)
    os.chdir(default_cwd)


def setup_cpp():
    print('--- Cpp')
    get_repo('cocos2d-x', 'https://github.com/cocos2d/cocos2d-x.git', './cpp/cocos2d', '90f6542')
    # no submodule update needed for this game, so just run download-deps.py
    subprocess.run(['python', './cpp/cocos2d/download-deps.py'])

    get_repo('jl_signal', 'https://github.com/jeffomatic/jl_signal.git', './cpp/third_party/jl_signal', '4c15aed')
    get_repo('rapidjson', 'https://github.com/Tencent/rapidjson.git', './cpp/third_party/rapidjson', '232389d')

    print('--- Replacing config files...')
    shutil.copyfile('./cpp/to_replace/cocos2d/cocos/base/ccConfig.h', './cpp/cocos2d/cocos/base/ccConfig.h')
    shutil.copyfile('./cpp/to_replace/cocos2d/cocos/CMakeLists.txt', './cpp/cocos2d/cocos/CMakeLists.txt')

    print('--- Done\n')


def setup_csharp():
    print('--- CSharp')
    dotween_repo_path = './csharp_unity/ThirdParty/DOTween'
    get_repo('DOTween', 'https://github.com/Demigiant/dotween.git', dotween_repo_path, '47e873e')

    print('--- Copying DOTween lib to Assets...')
    dotween_lib_path = './csharp_unity/Assets/DOTween'
    if os.path.isdir(dotween_lib_path):
        # remove old directory
        shutil.rmtree(dotween_lib_path)
    shutil.copytree(dotween_repo_path + '/_DOTween.Assembly/bin', dotween_lib_path)

    print('--- Done\n')


# select game version
cpp = 'cpp'
csharp = 'csharp'
both = 'both'

while True:
    setup_complete = False

    selected_game_version = input('Which version do you want to set up? Type "' + cpp + '", "' + csharp + '" or "' + both + '" (without quotes): ')
    if selected_game_version == cpp or selected_game_version == both:
        setup_cpp()
        setup_complete = True
    if selected_game_version == csharp or selected_game_version == both:
        setup_csharp()
        setup_complete = True

    if setup_complete:
        break
