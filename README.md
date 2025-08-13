# Ray Tracer

A C++ ray tracer inspired by Ray Tracing in One Weekend, developed to explore advanced rendering techniques, optimize performance, and apply modern C++ design patterns.

## Features
- **Modern C++** implementation with RAII and smart pointers
- **Multithreaded rendering** for significant performance gains
- **Optimized code structure** for readability and maintainability
- Supports spheres, materials, and realistic lighting

## Performance

Three implementations were benchmarked using the same scene and hardware:

| Implementation                          | Mean Time (s) | Median Time (s) | Std. Dev (s) |
|-----------------------------------------|---------------|-----------------|--------------|
| Original (Shirley's example)            | 77.6          | 78              | 1.02         |
| Refactored (no multithreading)          | 66.0          | 66              | 0.89         |
| Refactored + Multithreading (final)     | **26.0**      | **26**          | 1.90         |

<img width="1200" height="800" alt="raytracer_performance" src="https://github.com/user-attachments/assets/f8e06691-a195-4f7d-9792-d876005605e4" />
**Result:** The final multithreaded version achieved **~66% faster rendering** than the original implementation.

## Demo
<img width="996" height="561" alt="ray tracer" src="https://github.com/user-attachments/assets/2d4cb7b3-5a49-438e-ba8f-9507bb19af29" />
