project('glyph', 'c', version: '0.0.1')

gl_dep = dependency('gl')
glfw_dep = dependency('glfw3')

glyph_src = [
    'src/glyph.c',
    'glad/src/glad.c',
]

glyph = shared_library('glyph', 
  glyph_src,
  dependencies: [gl_dep, glfw_dep],
  include_directories: include_directories('include', 'glad/include'),
  gnu_symbol_visibility: 'hidden',
)


executable('testglyph', 
  'main.c', 
  link_with: glyph, 
  include_directories: include_directories('include'),
  dependencies: [gl_dep, glfw_dep]
)
