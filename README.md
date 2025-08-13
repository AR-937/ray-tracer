# Ray Tracer

A self-developed **C++ ray tracer** inspired by the _Ray Tracing in One Weekend_ series.  
The project was created to deepen my understanding of **rendering techniques**, **optimization**, and **modern C++ design**.

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

**Result:** The final multithreaded version achieved **~66% faster rendering** than the original implementation.

## Example Output
![Example Render](images/example.png)

## Technologies Used
- **C++17**
- **STL** (Standard Template Library)
- **Multithreading** (`std::thread`, `std::mutex`)
- **Mathematics for graphics** (vectors, ray-sphere intersection)
- **Linux**

## Project Structure
