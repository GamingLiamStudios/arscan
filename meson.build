project(
  'arscan',
  'cpp',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets', 'Svg', 'WaylandClient'], main: true)

dependencies = [
  qt6_dep
]

inc = [
  include_directories('src')
]

sources = files(
  'src/main.cpp',
  'src/ui/MainWindow.cpp',
)

moc_headers = [
  'src/ui/MainWindow.hpp',
]
sources += qt6.preprocess(
  moc_headers: moc_headers,
  include_directories: inc,
  dependencies: qt6_dep,
)

exe = executable(
  'arscan',
  sources: sources,
  include_directories: inc,
  dependencies : dependencies,

  win_subsystem: 'windows',
  install : true,
)

test('arcan', exe)
