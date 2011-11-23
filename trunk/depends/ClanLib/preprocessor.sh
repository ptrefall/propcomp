mv ../../src/types_config.h ../../src/types_config.h.old
sed -i 's/T_String/CL_String/g' ../../src/*.h ../../src/*.cpp
sed -i 's/D32/double/g' ../../src/*.h ../../src/*.cpp
sed -i 's/F32/float/g' ../../src/*.h ../../src/*.cpp
sed -i 's/S32/int/g' ../../src/*.h ../../src/*.cpp
sed -i 's/U32/unsigned int/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_PropertyTypeId/unsigned int/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_EntityId/unsigned long/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_Exception/CL_Exception/g' ../../src/*.h ../../src/*.cpp
sed -i 's/HAS_SIGNALSLOTS_INHERITANCE_TYPE//g' ../../src/*.h ../../src/*.cpp
sed -i 's/NULL_PTR/nullptr/g' ../../src/*.h ../../src/*.cpp
sed -i 's/typename T_Signal_v0<>::Type/CL_Signal_v0/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_Signal_v0<>::Type/CL_Signal_v0/g' ../../src/*.h ../../src/*.cpp
sed -i 's/typename T_Signal_v\(.*\)::Type/CL_Signal_v\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_Signal_v\(.*\)::Type/CL_Signal_v\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/typename T_SharedPtr\(.*\)::Type/CL_SharedPtr\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_SharedPtr\(.*\)::Type/CL_SharedPtr\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/typename T_Vector\(.*\)::Type/std::vector\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_Vector\(.*\)::Type/std::vector\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/typename T_Map\(.*\)::Type/std::unordered_map\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_Map\(.*\)::Type/std::unordered_map\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/typename T_Pair\(.*\)::Type/std::pair\1/g' ../../src/*.h ../../src/*.cpp
sed -i 's/T_Pair\(.*\)::Type/std::pair\1/g' ../../src/*.h ../../src/*.cpp
mv ../../src/types_config.h.old ../../src/types_config.h