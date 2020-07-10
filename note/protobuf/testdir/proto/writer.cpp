#include <iostream>
#include <fstream>
#include <string>

#include "addressbook.pb.h" 

using namespace std;

void PromptForAddress(turorial::Person* person)
{
	cout << "enter person ID:" << endl;
	int id;
	cin >> id;
	person->set_id(id);
	cin.ignore(256, '\n');

	cout << "enter name:";
	getline(cin, *person->mutable_name());  // ??? 

	cout << "enter email:";
	string email;
	getline(cin, email);
	if(!email.empty()) {
		person->set_email(email);
	}

	while(true) {
		cout << "enter a phone number";
		string number;
		getline(cin, number);

		if(number.empty()) {
			break;
		}

		turorial::Person::PhoneNumber* phone_number = person->add_phones();
		phone_number->set_number(number);

		cout << "is this a mobile, home or work phone?";
		string type;
		getline(cin, type);
		if(type=="mobile") {
			phone_number->set_type(turorial::Person::MOBILE);
		} else if(type=="home") {
			phone_number->set_type(turorial::Person::HOME);
		} else if(){
			phone_number->set_type(turorial::Person::WORK);
		} else {
			cout << "unknown phone type";
		}
	}
}


int main(int argc, char* argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if( argc!=2) {
		cerr << "usage    ddfasfas ";
		return -1;
	}

	turorial::AddressBook address_book;

	fstream input(argv[1], ios::in | ios::binary);

	if(!input) {
		cout << argv[1] << ": file not find";
	} else if(!address_book.ParseFromIstream(&input)){
		cerr << "failed to parse address book" << endl;
		return -1;
	}


	PromptForAddress(address_book.add_people());

	fstream output(argv[1], ios::out | ios::binary | ios::trunc);

	if(!address_book.SerializeToOstream(&output)) {
		cerr << "failed to write address book";
		return -1;
	}

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}