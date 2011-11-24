mv ../../include/Totem/types_config.h ../../include/Totem/types_config.h.old

find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_String/CL_String/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/D32/double/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/F32/float/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/S32/int/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/U32/unsigned int/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_PropertyTypeId/unsigned int/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_EntityId/unsigned long/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_Exception/CL_Exception/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/HAS_SIGNALSLOTS_INHERITANCE_TYPE//g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/NULL_PTR/nullptr/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/typename T_Signal_v0<>::Type/CL_Signal_v0/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_Signal_v0<>::Type/CL_Signal_v0/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/typename T_Signal_v\(.*\)::Type/CL_Signal_v\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_Signal_v\(.*\)::Type/CL_Signal_v\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/typename T_SharedPtr\(.*\)::Type/CL_SharedPtr\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_SharedPtr\(.*\)::Type/CL_SharedPtr\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/typename T_Vector\(.*\)::Type/std::vector\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_Vector\(.*\)::Type/std::vector\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/typename T_Map\(.*\)::Type/std::unordered_map\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_Map\(.*\)::Type/std::unordered_map\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/typename T_Pair\(.*\)::Type/std::pair\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/T_Pair\(.*\)::Type/std::pair\1/g' {} \;
find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/.bind(/.set(/g' {} \;
# find ../../src ../../include ../../examples ../../tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/->delegate(/->invoke(/g' {} \;

mv ../../include/Totem/types_config.h.old ../../include/Totem/types_config.h
