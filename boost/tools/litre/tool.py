try:
    import locale
    locale.setlocale(locale.LC_ALL, '')
except:
    pass


import sys
import docutils.writers
import cplusplus
import os

from docutils.core import publish_cmdline, default_description

class config:
    pass

description = ('Literate programming from ReStructuredText '
               'sources.  ' + default_description)

def _pop_option(prefix):
    found = None
    for opt in sys.argv:
        if opt.startswith(prefix):
            sys.argv = [ x for x in sys.argv if x != opt ]
            found = opt
            if prefix.endswith('='):
                found = opt[len(prefix):]
    return found


dump_dir = _pop_option('--dump_dir=')
max_output_lines = _pop_option('--max_output_lines=')

if dump_dir:
    
    cplusplus.Writer.translator = cplusplus.DumpTranslator
    if _pop_option('--workaround'):
        cplusplus.Writer.translator = cplusplus.WorkaroundTranslator
        config.includes.insert(0, os.path.join(os.path.split(dump_dir)[0], 'patches'))
        
    config.dump_dir = os.path.abspath(dump_dir)
    if _pop_option('--cleanup_source'):
        config.line_hash = None
        
    if not os.path.exists(config.dump_dir):
        os.makedirs(config.dump_dir)

if max_output_lines:
    config.max_output_lines = int(max_output_lines)

config.bjam_options = _pop_option('--bjam=')

config.includes = []

publish_cmdline(
    writer=cplusplus.Writer(config),
    description=description
    )
