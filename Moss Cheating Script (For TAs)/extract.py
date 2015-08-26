#!/usr/bin/python

from os import listdir, mkdir, remove
from shutil import move
from re import match

def main():
    files = dict()
    for file in listdir('.'):
        finfo = parsefilename(file)
        if finfo:
            files[file] = finfo

    actions = {
        'zip': extract('unzip %s -d %s'   ),
        'tar': extract('tar -xf %s -C %s' ),
        'bz2': extract('tar -xjf %s -C %s'),
        'tgz': extract('tar -xzf %s -C %s'),
        'gz' : extract('tar -xzf %s -C %s'),
        'rar': extract('unrar x %s %s'    ),
        '7z':  extract('7za e %s -o%s')
    }

    usrs = set()
    for file, info in files.items():
        usrs.add(info[1])
        ext = info[3]
        act = actions.get(ext, default)
        act(file, info)

    print 'Users: %d' % len(usrs)

def ensuredir(f):
    def wrap(file, info):
        try:
            mkdir(info[1])
        except: pass
        return f(file, info)
    return wrap

def cleanup(f):
    def wrap(file, info):
        try:
            return f(file, info)
        finally:
            remove(file)
    return wrap

@ensuredir
def default(file, info):
    move(file, '%s/%s' % (info[1], info[2]))

def extract(format_string):
    @cleanup
    @ensuredir
    def action(file, info):
        runcommand(format_string % (file, info[1]))
    return action

def runcommand(command):
    print command
    from shlex import split
    from subprocess import call
    cmd = split(command)
    call(cmd)

def parsefilename(filename):
    try:
        ext = filename[filename.rindex('.')+1:]
    except ValueError:
        ext = None

    # For assignment files
    m = match('([^_]*)_([a-z]{3}[0-9]{0,3})_(.*)', filename)
    if m:
        return m.group(1), m.group(2), m.group(3), ext

    # For comment files
    m = match(r'([^_]*)_([a-z]{3}[0-9]{0,3})\.txt', filename)
    if m:
        return m.group(1), m.group(2), 'comments.txt', 'txt'

if __name__ == '__main__':
    main()
