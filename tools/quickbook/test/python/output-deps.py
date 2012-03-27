#!/usr/bin/env python

import sys, os, subprocess, tempfile

def main(args, directory):
    if len(args) != 1:
        print "Usage: output-deps.py quickbook-command"
        exit(1)
    quickbook_command = args[0]
    failures = 0
    failures += run_quickbook(quickbook_command, 'svg_missing.qbk',
            deps_gold = 'svg_missing.txt')
    failures += run_quickbook(quickbook_command, 'missing_relative.qbk',
            deps_gold = 'missing_relative.txt')
    failures += run_quickbook(quickbook_command, 'include_path.qbk',
            deps_gold = 'include_path.txt',
            input_path = ['sub1', 'sub2'])
    print "Failures:",failures
    exit(failures)

def run_quickbook(quickbook_command, filename, output_gold = None,
        deps_gold = None, input_path = []):
    failures = 0

    command = [quickbook_command, '--debug', filename]

    output_filename = None
    if output_gold or not deps_gold:
        output_filename = temp_filename('.qbk')
        command.extend(['--output-file', output_filename])

    deps_filename = None
    if deps_gold:
        deps_filename = temp_filename('.txt')
        command.extend(['--output-deps', deps_filename])

    try:
        for path in input_path:
            command.extend(['-I', path])
        print 'Running: ' + ' '.join(command)
        print
        exit_code = subprocess.call(command)
        print
        success = not exit_code

        if output_filename:
            output = load_file(output_filename)
        else:
            output = None

        if deps_filename:
            deps = load_file(deps_filename)
        else:
            deps = None
    finally:
        if output_filename: os.unlink(output_filename)
        if deps_filename: os.unlink(deps_filename)

    if deps_gold:
        gold_deps = set(os.path.realpath(x) for x in
                load_file(deps_gold).strip().split('\n'))
        test_deps = set(deps.strip().split('\n'))
        if test_deps != gold_deps:
            failures = failures + 1
            print "Dependencies doesn't match:"
            print "Gold:", gold_deps
            print "Result:", test_deps
            print

    if output_gold:
        gold = load_file(output_gold)
        if output_gold != output:
            failures = failures + 1
            print "Output doesn't match:"
            print
            print output_gold
            print
            print gold
            print

    return failures

def temp_filename(extension):
    file = tempfile.mkstemp(suffix = extension)
    os.close(file[0])
    return file[1]

def load_file(filename):
    f = open(filename, 'r')
    try:
        return f.read()
    finally:
        f.close()

    return None

main(sys.argv[1:], os.path.dirname(sys.argv[0]))
