/*Totem EDK
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Totem EDK may link to may have additional
requirements or restrictions.
*/

#include <Component.h>
#include <ComponentFactory.h>
#include <PropertySerializer.h>

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "../Common/CustomPropertySerializer.h"
#include "../Common/Vector3.h"

using namespace Totem;

void printStartup();
void printReady(const T_String &msg);

void main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	
	CustomPropertySerializer serializer;
	Entity entity = Entity(factory, &serializer); //<-- push in "custom" serializer
	Property<Vector3<F32>> testVec3f = entity.addProperty<Vector3<F32>>("TestVec3f", Vector3<F32>(1.1f, 2.22f, 3.333f));
	Property<bool> testBool = entity.addProperty<bool>("TestBool", true);
	Property<S32> testInt = entity.addProperty<S32>("TestInt", -10);
	PropertyList<Vector3<S32>> testVec3iList = entity.addPropertyList<Vector3<S32>>("TestVec3iList");
	testVec3iList.push_back(Vector3<S32>(1,2,3));
	testVec3iList.push_back(Vector3<S32>(-1,-2,-3));

	//This should fail unless USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND is enabled in types_config.h
	try
	{
		PropertyList<bool> testBoolList = entity.addPropertyList<bool>("TestBoolList");
		testBoolList.push_back(true);
	}
	catch(T_Exception &e)
	{
		std::cout << "This exception is supposed to happen unless you enable USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND, so don't panic!" << std::endl;
		std::cout << "std::vector<bool> handling exception: " << e.what() << std::endl;
	}

	
	Entity entity2 = Entity(factory); //<-- instanciate "default" serializer
	Property<U32> testUInt = entity2.addProperty<U32>("TestUInt", 20);
	Property<F32> testFloat = entity2.addProperty<F32>("TestFloat", 30.5f);
	PropertyList<F32> testFloatList = entity2.addPropertyList<F32>("TestFloatList");
	testFloatList.push_back(-1.1f);
	testFloatList.push_back(-2.22f);
	testFloatList.push_back(-3.333f);

	printReady("Original values:");

	std::cout << "Vec3f: " << testVec3f.get().x << " " << testVec3f.get().y << " " << testVec3f.get().z << std::endl;
	std::cout << "Bool: " << testBool.get() << std::endl;
	std::cout << "Int: " << testInt.get() << std::endl;
	std::cout << "UInt: " << testUInt.get() << std::endl;
	std::cout << "Float: " << testFloat.get() << std::endl;
	
	std::cout << "Vec3i List: ";
	for(U32 i = 0; i < testVec3iList.size(); i++)
		std::cout << testVec3iList.get()[i].x << " " << testVec3iList.get()[i].y << " " << testVec3iList.get()[i].z << " ";
	std::cout << std::endl;
	
	std::cout << "Float List: ";
	for(U32 i = 0; i < testFloatList.size(); i++)
		std::cout << testFloatList.get()[i] << " ";
	std::cout << std::endl;

	printReady("Serialized values:");

	T_String strVec3f = testVec3f.toString();
	T_String strBool = testBool.toString();
	T_String strInt = testInt.toString();
	T_String strUInt = testUInt.toString();
	T_String strFloat = testFloat.toString();
	T_String strVec3iList = testVec3iList.toString();
	T_String strFloatList = testFloatList.toString();

	std::cout << "Vec3f: " << strVec3f.c_str() << std::endl;
	std::cout << "Bool: " << strBool.c_str() << std::endl;
	std::cout << "Int: " << strInt.c_str() << std::endl;
	std::cout << "UInt: " << strUInt.c_str() << std::endl;
	std::cout << "Float: " << strFloat.c_str() << std::endl;
	std::cout << "Vec3i List: " << strVec3iList.c_str() << std::endl;
	std::cout << "Float List: " << strFloatList.c_str() << std::endl;

	printReady("Deserialized values:");

	testVec3f.fromString(strVec3f);
	testBool.fromString(strBool);
	testInt.fromString(strInt);
	testUInt.fromString(strUInt);
	testFloat.fromString(strFloat);
	testVec3iList.fromString(strVec3iList);
	testFloatList.fromString(strFloatList);

	std::cout << "Vec3f: " << testVec3f.get().x << " " << testVec3f.get().y << " " << testVec3f.get().z << std::endl;
	std::cout << "Bool: " << testBool.get() << std::endl;
	std::cout << "Int: " << testInt.get() << std::endl;
	std::cout << "UInt: " << testUInt.get() << std::endl;
	std::cout << "Float: " << testFloat.get() << std::endl;

	std::cout << "Vec3i List: ";
	for(U32 i = 0; i < testVec3iList.size(); i++)
		std::cout << testVec3iList.get()[i].x << " " << testVec3iList.get()[i].y << " " << testVec3iList.get()[i].z << " ";
	std::cout << std::endl;
	
	std::cout << "Float List: ";
	for(U32 i = 0; i < testFloatList.size(); i++)
		std::cout << testFloatList.get()[i] << " ";
	std::cout << std::endl;

	system("pause");
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out Totem EDK!" << std::endl;
	std::cout << "In this test we'll demonstrate the serialization API of Totem EDK." << std::endl;
	std::cout << "\n";
}

void printReady(const T_String &msg)
{
	system("pause");
	std::cout << "\n" << msg << "\n";
}
