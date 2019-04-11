#include <iosteram>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

using namespace std;

void ListPeople(const turorial::AddressBook& address_book){
	for(int i=0; i<address_book.people_size(); i++) {
        const tutorial::Person& person = address_book.people(i);
        cout << "Person ID:" << person.id() << endl;
        cout << "  Name:" << person.name() << endl;
        if(person.has_email()) {
            cout << "   email address:" << person.email() << endl;
        }

        for(int j=0; j<person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type())
            {
                case tutorial::Person::MOBILE :
                    cout << " Mobile phone# ";
                    break;
                case tutorial::Person::HOME :
                    cout << " HOME phone# ";
                    break;
                case tutorial::Person::WORK :
                    cout << " WORK phone# ";
                    break;
            
                default:
                    break;
            }
            cout << phone_number.number() << endl;
        }
    }
}


int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if(argc!2) {
        cerr << "usage error";
        return -1;
    }

    tutorial::AddressBook address_book;

    fstream input(argv[1], ios::in|ios::binary);
    if(!address_book.ParseFromIstream(&input)) {
        cerr << "failed to parse address book" << endl;
        return -1;
    }

    ListPeople(address_book);

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}