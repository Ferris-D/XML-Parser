#include "Human.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>

int main(int *argv,char argc[])
{
	std::string command;
	tinyxml2::XMLDocument savedObject;
	std::cout << "Type 'new' to make a new object\nType 'load' to load an object from XML" << std::endl;
	std::getline(std::cin, command);
	if (command == "new") // If user writes new we make a new object take in custom values and save it
	{
		Human human;
		std::cout << "Name: ";
		std::getline(std::cin, command);
		human.name = command;
		std::cout << "Age: ";
		std::getline(std::cin, command);
		human.age = std::stoi(command);
		std::cout << "Weight: ";
		std::getline(std::cin, command);
		human.weight = std::stoi(command);
		// After the values are written to the object save it
		std::cout << "Saving file to XML" << std::endl;
		std::string fn = human.name;
		fn.append(".xml");
		savedObject.LoadFile(fn.c_str());
		savedObject.Clear();
		// Add all the data
		tinyxml2::XMLNode* root = savedObject.NewElement("Root"); // Root element
		savedObject.InsertEndChild(root);
		// Name element
		tinyxml2::XMLElement* data = savedObject.NewElement("Name");
		data->SetText(human.name.c_str());
		root->InsertEndChild(data);
		// Age element
		data = savedObject.NewElement("Age");
		data->SetText(human.age);
		root->InsertEndChild(data);
		// Weight element
		data = savedObject.NewElement("Weight");
		data->SetText(human.weight);
		root->InsertEndChild(data);
		// Save the file
		savedObject.SaveFile(fn.c_str());
		std::cout << "Saved " << human.name << std::endl;
	}
	else if (command == "load") // If user writes load we take a filename to load then print the values
	{
		Human human;
		std::cout << "Load filename: "; // Take in a filename to load
		std::getline(std::cin, command);
		savedObject.LoadFile(command.c_str());
		if (savedObject.Error())
		{
			std::cout << "Error loading " << command << std::endl;
			return 0;
		}
		tinyxml2::XMLNode* root = savedObject.FirstChild();
		tinyxml2::XMLElement* data = root->FirstChildElement("Name"); // Get name element
		human.name = data->GetText();
		data = root->FirstChildElement("Age"); // Get age element
		human.age = data->IntText();
		data = root->FirstChildElement("Weight"); // Get weight element
		human.weight = data->IntText();
		std::cout << "Object loaded..." << std::endl;
		std::cout << "Name: " << human.name << std::endl;
		std::cout << "Age: " << human.age << std::endl;
		std::cout << "Weight: " << human.weight << std::endl;
	}
	return 0;
}