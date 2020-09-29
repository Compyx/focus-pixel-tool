# vim: set syntax=meson:
#
# Meson build file for the Focus Pixel Tool


# Set project name and default language
project('focus-pixel-tool',
        'c',
        default_options : ['c_std=c99'])



# Set config.h
conf_data = configuration_data()
conf_data.set('prgname', 'Focus Pixel Tool')
conf_data.set('prgversion', '0.0.1')
configure_file(input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

# Import Gnome/Gtk helpers module
gnome = import('gnome')

# Set dependencies
dep_gtk = dependency('gtk+-3.0')

# Set GResource compiler
gresource_compiler = find_program('glib-compile-resources')

# Compile resources
app_resources = gnome.compile_resources(
    'app-resources', 'data/resources.xml',
    source_dir : ['data', 'data/ui'],
    c_name: 'app',
    extra_args : '--manual-register')

# Set include dirs
incdirs = include_directories('.', 'src', 'src/ui')

warnings = ['-Wall', '-Wextra', '-Wno-unused-parameter']

# I guess this is autohell's "all"?
executable('focus-pixel-tool',
           ['src/main.c', 'src/ui/mainwindow.c', 'src/debug.h',
            'src/ui/about.c'],
           app_resources,
           include_directories : incdirs,
           dependencies : [dep_gtk],
           c_args : warnings)
