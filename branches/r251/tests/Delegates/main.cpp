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

#include "../Common/Entity.h"
#include <Totem/Component.h>
#include <Totem/ComponentFactory.h>

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace Totem;

void printStartup();
void initFactory(ComponentFactory &factory);
void printReady();

class ComponentA : public Component
{
public:
	COMPONENT_0(Entity, ComponentA)
	ComponentA(Entity &owner, const T_String &name)
	: Component(name), owner(owner), intricateAlgId("INTRICATE_ALG"), translateToNorwegianId("TRANSLATE_NOR")
	{
		owner.registerFunction2<const F32 &, const F32 &, F32>(intricateAlgId).bind(this, &ComponentA::intricateAlgorithm);
		owner.registerFunction1<const T_String &, T_String>(translateToNorwegianId).bind(this, &ComponentA::translateToNorwegian);
	}
	virtual ~ComponentA() {}

private:
	F32 intricateAlgorithm(const F32 &param1, const F32 &param2)
	{
		std::cout << "Intricate Algorithm in ComponentA called with parameters " << param1 << ", " << param2 << std::endl;
		return param1 * param1 + param2 * param2;
	}
	T_String translateToNorwegian(const T_String &word)
	{
		std::cout << "Translate To Norwegian in ComponentA called with parameter " << word.c_str() << std::endl;
		if(word == "Hello")
			return "Hei";
		else if(word == "Bye")
			return "Hadet";
		return "No idea how to translate that...";
	}

	T_HashedString intricateAlgId, translateToNorwegianId;
};

class ComponentB : public Component
{
public:
	COMPONENT_0(Entity, ComponentB)
	ComponentB(Entity &owner, const T_String &name)
	: Component(name), owner(owner), wordTranslatorId("WORD_TRANSLATOR"), translateToNorwegianId("TRANSLATE_NOR"), crazyFuncId("CRAZY_FUNC")
	{
		owner.registerFunction2<const T_String &, const T_String &, T_Void>(wordTranslatorId).bind(this, &ComponentB::wordTranslator);
		owner.registerFunction6<U32, S32, F32, U32, S32, const T_String &, F32>(crazyFuncId).bind(this, &ComponentB::crazyFunction);
	}
	virtual ~ComponentB() {}

private:
	T_Void wordTranslator(const T_String &word, const T_String &language)
	{
		if(language == "Norwegian")
		{
			T_String translated_word = owner.call1<const T_String &, T_String>(translateToNorwegianId, word);
			std::cout << word.c_str() << " in norwegian is " << translated_word.c_str() << std::endl;
		}
		return NULL_PTR;
	}

	F32 crazyFunction(U32 param1, S32 param2, F32 param3, U32 param4, S32 param5, const T_String &param6)
	{
		std::cout << "Crazy Function called with eight parameter being " << param6.c_str() << std::endl;
		return ((F32)param1 + (F32)param2 + param3 + (F32)param4 - (F32)param5 );
	}

	T_HashedString wordTranslatorId, translateToNorwegianId, crazyFuncId;
};

int main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	initFactory(factory);

	std::cout << "Define test Entity..." << std::endl;
	std::cout << "- add ComponentA component" << std::endl;
	std::cout << "- add ComponentB component" << std::endl;

	Entity test = Entity(factory);
	test.addComponent("ComponentA");
	test.addComponent("ComponentB");

	printReady();

	F32 value = test.call2<const F32 &, const F32 &, F32>(T_HashedString("INTRICATE_ALG"), 2.0f, 4.0f);
	std::cout << "Result: " << value << std::endl << std::endl;

	value = test.call6<U32, S32, F32, U32, S32, const T_String &, F32>(T_HashedString("CRAZY_FUNC"), 2, 1, 4.0f, 8, -2, "This is crazy!");
	std::cout << "Result: " << value << std::endl << std::endl;

	test.call2<const T_String &, const T_String &, T_Void>(T_HashedString("WORD_TRANSLATOR"), "Hello", "Norwegian");
	test.call2<const T_String &, const T_String &, T_Void>(T_HashedString("WORD_TRANSLATOR"), "Bye", "Norwegian");

	system("pause");
	return 0;
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out Totem EDK!" << std::endl;
	std::cout << "In this test we'll demonstrate some of the features of Delegates." << std::endl;
	std::cout << "\n";
	system("pause");
}

void initFactory(ComponentFactory &factory)
{
	std::cout << "Initialize components..." << std::endl;
	std::cout << "- register ComponentA" << std::endl;
	std::cout << "- register ComponentB" << std::endl;

	ComponentA::RegisterToFactory(factory);
	ComponentB::RegisterToFactory(factory);
}

void printReady()
{
	std::cout << "Initialization done." << std::endl;
	std::cout << "Press any key to start simulation." << std::endl;
	std::cout << "\n";
	system("pause");
}
