proyectogui_sources = [
  'main.c',
  'proyectogui-application.c',
  'proyectogui-window.c',
]

proyectogui_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

proyectogui_sources += gnome.compile_resources('proyectogui-resources',
  'proyectogui.gresource.xml',
  c_name: 'proyectogui'
)

executable('proyectogui', proyectogui_sources,
  dependencies: proyectogui_deps,
  install: true,
)
