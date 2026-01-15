# generate_cpp_array.py
import sys

# --- Config ---
input_file = "../Resources/BishopMagics.txt"    
output_name = "ROOK_MAGICS"         
namespace = "MagicBB"               

# --- Read magic numbers ---
with open(input_file, "r") as f:
    lines = f.readlines()

# Clean lines and make sure they are valid
magic_numbers = [line.strip() for line in lines if line.strip()]

# --- Generate C++ array ---
print(f"namespace {namespace} {{")
print(f"const std::array<uint64_t, {len(magic_numbers)}> {output_name} = {{")

for i, num in enumerate(magic_numbers):
    end = "," if i < len(magic_numbers) - 1 else ""
    print(f"    {num}ULL{end}")

print("};")
print("} // namespace", namespace)
