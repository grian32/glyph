project('glyph', 'c', version: '0.0.1')

gl_dep = dependency('gl')
glfw_dep = dependency('glfw3')
jxl_dep = dependency('libjxl')

glyph_src = [
    'src/glyph/glyph.c',
    'glad/src/glad.c',
    'src/glyph/window.c',
    'src/glyph/renderer.c',
    'src/glyph/shaders.c',
    'src/glyph/math.c',
    'src/glyph/camera.c',
    'src/glyph/input.c',
    'src/glyph/texture.c',
]

vert_h = custom_target('shader_vert',
    input: 'src/glyph/shaders/shader.vert',
    output: 'shader_vert.h',
    command: ['xxd', '-i', '-n', 'vert_src', '@INPUT@', '@OUTPUT@'],
)

frag_h = custom_target('shader_frag',
    input: 'src/glyph/shaders/shader.frag',
    output: 'shader_frag.h',
    command: ['xxd', '-i', '-n', 'frag_src', '@INPUT@', '@OUTPUT@'],
)

glyph = shared_library('glyph',
    glyph_src,
    vert_h,
    frag_h,
    dependencies: [gl_dep, glfw_dep, jxl_dep],
    link_args: ['-lm'],
    include_directories: include_directories('include', 'src', 'glad/include'),
    gnu_symbol_visibility: 'hidden',
)

executable('testglyph',
    'main.c',
    link_with: glyph,
    link_args: ['-lm'],
    include_directories: include_directories('include'),
    dependencies: [gl_dep, glfw_dep]
)
