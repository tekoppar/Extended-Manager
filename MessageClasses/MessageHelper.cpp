#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Adresses.h"

#include "MessageHelper.h"

app::MessageControllerB* MessageHelper::MessageControllerB = nullptr;

app::GameObject* MessageHelper::CreateMessagebox(std::string text, tem::Vector3 position, float duration)
{
	if (MessageControllerB == nullptr)
	{
		app::Type* MessageControllerBType = GetType("", "MessageControllerB");
		app::Object_1__Array* MessageControllerBArr = app::Object_1_FindObjectsOfTypeAll(MessageControllerBType, NULL);

		MessageControllerB = (app::MessageControllerB*)MessageControllerBArr->vector[0];
	}

	auto Class2 = GetClass<>("", "MessageDescriptor");
	app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
	app::String* messageText1 = string_new(text.data());
	app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);

	app::GameObject* MessageBoxObject = app::MessageControllerB_ShowMessageBox_1(MessageControllerB, MessageControllerB->fields.HintMessage, messageDescriptor->fields, position.ToMoon(), duration, messageText1, messageText1, NULL);

	/*app::Vector3* anchorSize = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
	anchorSize->x = 0;
	anchorSize->y = 0;

	auto Class2 = GetClass<>("", "MessageDescriptor");
	app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
	app::String* messageText1 = string_new("test<xbox>p</>");
	app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);

	app::MessageBox* newBox = app::MessageControllerB_ShowHintMessage_1(MessageControllerB, messageDescriptor->fields, *anchorSize, 10.0f, NULL);
	//newBox->fields.MessageIndex = 1;

	auto Class1 = GetClass<>("", "MessageBox");
	app::MessageBox* MessageBox = (app::MessageBox*)il2cpp_object_new((Il2CppClass*)Class1);

	app::String* messageText = string_new("MessageBox");
	app::MessageBox__ctor(MessageBox, NULL);
	app::GameObject__ctor((app::GameObject*)MessageBox, messageText, NULL);
	MessageBox->fields.LanguageStyles = newBox->fields.LanguageStyles;
	MessageBox->fields.TextBox = newBox->fields.TextBox;
	MessageBox->fields.Visibility = newBox->fields.Visibility;

	MessageBox->fields.OverrideText = messageText1;
	MessageBox->fields.m_currentMessage = messageDescriptor->fields;
	MessageBox->fields.Visibility->fields.DestroyOnHide = false;
	MessageBox->fields.Visibility->fields.m_time = 999999999.0f;
	app::MessageBox_SetMessageFade(MessageBox, 10, NULL);
	app::MessageBox_RefreshText(MessageBox, NULL);*/

		return MessageBoxObject;
}

app::GameObject* MessageHelper::CreateMessageboxNoBackground(std::string text, tem::Vector3 position, float duration)
{
	if (MessageControllerB == nullptr)
	{
		app::Type* MessageControllerBType = GetType("", "MessageControllerB");
		app::Object_1__Array* MessageControllerBArr = app::Object_1_FindObjectsOfTypeAll(MessageControllerBType, NULL);

		MessageControllerB = (app::MessageControllerB*)MessageControllerBArr->vector[0];
	}

	auto Class2 = GetClass<>("", "MessageDescriptor");
	app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
	app::String* messageText1 = string_new(text.data());
	app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);

	app::GameObject* MessageBoxObject = app::MessageControllerB_ShowMessageBox_1(MessageControllerB, MessageControllerB->fields.HintMessage, messageDescriptor->fields, position.ToMoon(), duration, messageText1, messageText1, NULL);
	
	//app::MessageBox_1* messageBox = (app::MessageBox_1*)MessageBoxObject;// (app::MessageBox*)GetComponentByType(MessageBoxObject, "Moon.UI", "MessageBox");
	//messageBox->fields.OverrideSize = textSize;
	//messageBox->fields.TextBox->fields.size = textSize;

	auto particleSystem = GetComponentsByTypeInChildren(MessageBoxObject, "UnityEngine", "ParticleSystem");
	app::GameObject* particleSystemObject = app::Component_1_get_gameObject(particleSystem[0], NULL);
	app::GameObject* parentParticle = TransformGetParent(particleSystemObject);
	app::Object_1_Destroy_1((app::Object_1*)parentParticle, NULL);

	return MessageBoxObject;
}

app::NPCMessageBox* MessageHelper::CreateNPCInteractionBox(std::string text, tem::Vector3 position, float duration)
{
	if (MessageControllerB == nullptr)
	{
		app::Type* MessageControllerBType = GetType("", "MessageControllerB");
		app::Object_1__Array* MessageControllerBArr = app::Object_1_FindObjectsOfTypeAll(MessageControllerBType, NULL);

		MessageControllerB = (app::MessageControllerB*)MessageControllerBArr->vector[0];
	}

	auto Class2 = GetClass<>("", "MessageDescriptor");
	app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
	app::String* messageText1 = string_new(text.data());
	app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);

	app::GameObject* MessageBoxObject = (app::GameObject*)app::MessageControllerB_ShowMessageBox_1(MessageControllerB, MessageControllerB->fields.NPCInteractionMessage, messageDescriptor->fields, position.ToMoon(), duration, messageText1, messageText1, NULL);
	app::NPCMessageBox* messageBox = (app::NPCMessageBox*)GetComponentByType(MessageBoxObject, "", "NPCMessageBox");

	//app::GameObject* buttonA = MessageHelper::CreateMessagebox("A", tem::Vector3(0, 0, 0), duration);

	auto ClassAction = GetClass<>("System", "Action");
	app::Action* newAction = (app::Action*)il2cpp_object_new((Il2CppClass*)ClassAction);
	app::Action__ctor(newAction, (app::Object*)MDV::MoonGameController, &app::GameController_RestoreCheckpointImmediate, NULL);
	newAction->fields._._.method_ptr = (void*)(Assembly_BaseAddr + 0x997580);
	newAction->fields._._.m_target = (app::Object*)MDV::MoonGameController;

	/*auto Class4 = GetClass<>("System", "Action");
	app::Type* type1 = GetType("UnityEngine", "GameObject");
	app::Action* action = (app::Action*)il2cpp_object_new((Il2CppClass*)Class4);
	app::Object* object1 = app::Activator_CreateInstance_4(type1, NULL);
	app::Action__ctor(action, NULL, &MessageHelper::ButtonAClicked, NULL);*/

	/*auto classButton = GetClass<>("Moon.UI", "Button");
	app::Button* buttonA = (app::Button*)il2cpp_object_new((Il2CppClass*)classButton);
	app::Button_1__ctor(buttonA, NULL);


	auto Class3 = GetClass<>("Moon.InteractionGraph", "InteractionBinding");
	app::InteractionBinding* interactionBinding = (app::InteractionBinding*)il2cpp_object_new((Il2CppClass*)Class3);
	app::InteractionBinding__ctor(interactionBinding, newAction, (app::IMessageProvider*)messageBox->fields.MessageBox->fields.MessageProvider, 0.0f, NULL);
	app::NPCMessageBox_LayoutButton(messageBox, interactionBinding, buttonA, NULL);
	messageBox->fields.AInteractionBinding = interactionBinding;
	messageBox->fields.ButtonA = buttonA;

	app::NPCMessageBox_LayoutButtons(messageBox, NULL);*/

	return messageBox;
}

void MessageHelper::ButtonAClicked()
{
	bool nowayitworks = false;
}

void MessageHelper::SetMessage(app::GameObject* messageBoxObject, std::string text, float textSize, app::Color* color)
{
	if (messageBoxObject->fields._.m_CachedPtr != nullptr)
	{
		auto Class2 = GetClass<>("", "MessageDescriptor");
		app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
		app::String* messageText1 = string_new(text.data());
		app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);
		app::String* empty = string_new("");

		app::MessageBox* messageBox = (app::MessageBox*)GetComponentByType(messageBoxObject, "", "MessageBox");

		if (messageBox != nullptr)
		{
			app::MessageBox_SetMessage(messageBox, messageDescriptor->fields, empty, empty, NULL);

			auto textboxese = GetComponentsByTypeInChildren(messageBoxObject, "CatlikeCoding.TextBox", "TextBox");
			app::TextBox* textBox = (app::TextBox*)textboxese[0];

			if (textBox != nullptr && textBox->fields._._._._.m_CachedPtr != nullptr)
			{
				//TransformSetScale((app::GameObject*)textBox, tem::Vector3(textSize * 0.02f, textSize * 0.02f, textSize * 0.02f));

				if (color == nullptr)
				{
					textBox->fields.color.a = textBox->fields.color.b = textBox->fields.color.g = textBox->fields.color.r = 1.0f;
				}
				else
					textBox->fields.color = *color;
			}
		}
	}
}