#include "tests.h"

void TrenchCoatgetName_TrenchCoat_CorrectName()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };

	assert(coat.getName().compare("name") == 0);
}

void TrenchCoatgetSize_TrenchCoat_CorrectSize()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };

	assert(coat.getSize().compare("size") == 0);
}

void TrenchCoatgetPhotographSource_TrenchCoat_CorrectPhotographSource()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };

	assert(coat.getPhotographSource().compare("photographSource") == 0);
}

void TrenchCoatCSVInsertionExtractionOperator_Coat_CoatWrittenInFile()
{
	std::ofstream fout(TestFile);

	TrenchCoat coat{ "name", "size", "source", 4 };

	fout << coat;

	fout.close();

	std::ifstream fin(TestFile);

	CSVTrenchCoat coatFromFile;

	fin >> coatFromFile;

	assert(coatFromFile.to_string() == coat.to_string());
	
	fin.close();

	std::ofstream clearFile(TestFile);
	clearFile.close();
}

void TrenchCoatOperatorEqual_ValidCoat_SameCoat()
{
	TrenchCoat coat1{"name", "size", "source", 5}, coat2;
	coat2 = coat1;
	coat1 = coat1;
	assert(coat1.to_string() == coat2.to_string());
}

void TrenchCoatHTMLInsertionExtractionOperator_Coat_CoatWrittenInFile()
{
	std::ofstream fout(TestFile);

	HTMLTrenchCoat coat{ "name", "size", "source", 4 };

	fout << coat;

	fout.close();

	std::ifstream fin(TestFile);

	HTMLTrenchCoat coatFromFile;

	fin >> coatFromFile;

	assert(coatFromFile.to_string() == coat.to_string());

	fin.close();

	std::ofstream clearFile(TestFile);
	clearFile.close();

}
void test_TrenchCoat()
{
	TrenchCoatgetName_TrenchCoat_CorrectName();
	TrenchCoatgetSize_TrenchCoat_CorrectSize();
	TrenchCoatgetPhotographSource_TrenchCoat_CorrectPhotographSource();
	TrenchCoatCSVInsertionExtractionOperator_Coat_CoatWrittenInFile();
	TrenchCoatHTMLInsertionExtractionOperator_Coat_CoatWrittenInFile();
	TrenchCoatOperatorEqual_ValidCoat_SameCoat();
}

void FileRepositoryStoreCoat_ValidCoat_CoatStored()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	std::vector<TrenchCoat> coats = repo.getAllCoats();

	assert(coats.size() == 1);

	repo.clearFile();
}

void FileRepositoryStoreCoat_DuplicateCoat_CoatNotStored()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);
	
	try
	{
		repo.storeCoat(coat);
		assert(false);
	}
	catch (ExistentTrenchCoat&)
	{
		assert(true);
	}
	repo.clearFile();
}

void FileRepositoryDeleteCoat_ValidCoat_CoatDeleted()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	repo.deleteCoat("name");

	assert(repo.getAllCoats().size() == 0);

	repo.clearFile();
}

void FileRepositoryDeleteCoat_InvalidCoat_CoatNotDeleted()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	try
	{
		repo.deleteCoat("Name1");
		assert(false);
	}
	catch (InexistentTrenchCoat&)
	{
		assert(true);
	}
	repo.clearFile();
}

void FileRepositoryUpdateCoat_ValidCoat_CoatUpdated()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 }, newCoat{ "name", "newSize", "newSource", 10 };

	repo.storeCoat(coat);

	repo.updateCoat(newCoat);

	std::vector<TrenchCoat> coats = repo.getAllCoats();

	assert(coats.size() == 1 
		&& coats[0].to_string() == newCoat.to_string());

	repo.clearFile();
}

void FileRepositoryUpdateCoat_InvalidCoat_ExceptionRaised()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 }, newCoat{ "name", "newSize", "newSource", 10 };

	repo.storeCoat(coat);

	repo.updateCoat(newCoat);
	
	try
	{
		repo.updateCoat(TrenchCoat("InexistentName", "size", "source", 10));
		assert(false);
	}
	catch (InexistentTrenchCoat&)
	{
		assert(true);
	}
	repo.clearFile();
}

void FileRepositoryGetCoatFromRepository_ValidIndex_CorrectCoat()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	assert(repo.getCoatFromRepository(0).to_string() == coat.to_string());

	repo.clearFile();
}

void FileRepositoryGetCoatFromRepository_InvalidIndex_ExceptionThrown()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	try
	{
		TrenchCoat coat = repo.getCoatFromRepository(1);
		assert(false);
	}
	catch(BadPosition&)
	{
		assert(true);
	}

	repo.clearFile();
}

void FileRepositoryFindCoatFromRepository_ValidName_CorrectCoat()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	TrenchCoat foundCoat = repo.findCoatFromRepository("name");

	assert(coat.to_string() == foundCoat.to_string());
	
	repo.clearFile();
}

void FileRepositoryFindCoatFromRepository_InvalidName_Exception()
{
	CSVFileRepository repo{ TestFile };

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	try
	{
		TrenchCoat foundCoat = repo.findCoatFromRepository("name1");
		assert(false);
	}
	catch(InexistentTrenchCoat&)
	{
		assert(true);
	}
	repo.clearFile();
}

void FileRepositoryGetRepositoryLength_RepositoryWithOneElement_One()
{
	CSVFileRepository repo{};
	repo.setPath(TestFile);

	TrenchCoat coat{ "name", "size","source", 5 };

	repo.storeCoat(coat);

	assert(repo.getRepositoryLength() == 1);
	repo.clearFile();
}

void HTMLFileRepositoryGetAllCoats_RepositoryWithOneCoat_OneCoatReturned()
{
	HTMLFileRepository repo{ TestFile };
	TrenchCoat coat{ "name", "size", "source", 4 };
	repo.storeCoat(coat);

	std::vector<TrenchCoat> coats = repo.getAllCoats();
		
	assert(coats.size() == 1 && coats[0].to_string() == coat.to_string());
	
	repo.clearFile();
}

void test_FileRepository()
{
	FileRepositoryStoreCoat_ValidCoat_CoatStored();
	FileRepositoryStoreCoat_DuplicateCoat_CoatNotStored();
	FileRepositoryDeleteCoat_ValidCoat_CoatDeleted();
	FileRepositoryDeleteCoat_InvalidCoat_CoatNotDeleted();
	FileRepositoryUpdateCoat_ValidCoat_CoatUpdated();
	FileRepositoryUpdateCoat_InvalidCoat_ExceptionRaised();
	FileRepositoryGetCoatFromRepository_ValidIndex_CorrectCoat();
	FileRepositoryGetCoatFromRepository_InvalidIndex_ExceptionThrown();
	FileRepositoryFindCoatFromRepository_ValidName_CorrectCoat();
	FileRepositoryFindCoatFromRepository_InvalidName_Exception();
	FileRepositoryGetRepositoryLength_RepositoryWithOneElement_One();
	HTMLFileRepositoryGetAllCoats_RepositoryWithOneCoat_OneCoatReturned();

}

void clearFiles()
{
	std::ofstream fTestFile{ TestFile };
	fTestFile.close();
	std::ofstream fUserCSV{ UserListTestFileCSV };
	fUserCSV.close();
	std::ofstream fUserHTML{ UserListTestFileHTML };
	fUserHTML.close();
}

void CoatServiceStoreCoat_ValidCoat_CoatAdded()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	
	service.storeCoatService("name", "size", "photoSource", "3");
	
	assert(service.getCoatFromRepository(0).to_string() == TrenchCoat("name", "size", "photoSource", 3).to_string());
	
	clearFiles();
}

void CoatServiceStoreCoat_InvalidCoat_CoatNotAdded()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");

	try
	{
		service.storeCoatService("name", "size", "photoSource", "3");
		assert(false);
	}
	catch(ExistentTrenchCoat&)
	{
		assert(true);
	}

	clearFiles();
}

void CoatServiceStoreCoat_InvalidCoatPrice_ExceptionRaised()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");

	try
	{
		service.storeCoatService("name1", "size", "source", "4asd");
		assert(false);
	}
	catch (InvalidCoat&)
	{
		assert(true);
	}

	clearFiles();
}

void CoatServiceDeleteCoat_ValidCoat_CoatDeleted()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");

	service.storeCoatService("name1", "size", "photoSource", "3");

	service.deleteCoatService("name");
	assert(service.getCoatFromRepository(0) == TrenchCoat("name1", "size", "photoSource", 3)
			&& service.getRepositoryLength() == 1);

	clearFiles();
}

void CoatServiceDeleteCoat_InvalidCoat_CoatNotDeleted()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");

	service.deleteCoatService("name");

	try
	{
		service.deleteCoatService("name");
		assert(false);
	}
	catch(InexistentTrenchCoat&)
	{
		assert(true);
	}
	clearFiles();
}

void CoatServiceUpdateCoat_ValidCoat_UpdatedCoat()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");
	service.updateCoatService("name", "newSize", "newPhotoSource", "5");

	std::vector<TrenchCoat> listOfCoats = service.listCoats();

	TrenchCoat coat = listOfCoats[0];

	assert(coat.to_string() == TrenchCoat("name", "newSize", "newPhotoSource", 5).to_string());

	clearFiles();
}

void CoatServiceUpdateCoat_InexistentCoat_Exception()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");
	try
	{
		service.updateCoatService("name1", "newSize", "newPhotoSource", "5");
		assert(false);
	}
	catch(InexistentTrenchCoat&)
	{
		assert(true);
	}
	clearFiles();
}

void CoatServiceUpdateCoat_InvalidCoatPrice_ExceptionRaised()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "photoSource", "3");

	try
	{
		service.updateCoatService("name", "size", "source", "4asd");
		assert(false);
	}
	catch (InvalidCoat&)
	{
		assert(true);
	}

	clearFiles();
}

void CoatServiceSaveTrenchCoatToUserList_ValidCoat_CoatAdded()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	service.setUserRepositoryPath(UserListTestFileCSV);
	service.storeCoatService("name", "size", "source", "3");

	service.saveTrenchCoatToUserList("name");

	assert(service.getUserCoats()[0] == TrenchCoat("name", "size", "source", 3));

	clearFiles();
}

void CoatServiceDeleteCoat_UserListWithOneCoat_DeletesTheCoatFromUserList()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	service.setUserRepositoryPath(UserListTestFileHTML);

	service.storeCoatService("name", "size", "source", "3");

	service.saveTrenchCoatToUserList("name");

	service.deleteCoatService("name");

	assert(service.getUserCoats().size() == 0);
	
	clearFiles();
}

void CoatServiceListFilteredCoats_ThreeCoats_OneCoatAfterFilter()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	service.setUserRepositoryPath(UserListTestFileCSV);


	service.storeCoatService("name", "size", "source", "3");
	service.storeCoatService("name1", "size", "source", "5");
	service.storeCoatService("name2", "size2", "source", "3");

	std::vector<TrenchCoat> filtered = service.listFilteredCoats("size", "3");

	assert(filtered[0] == TrenchCoat("name", "size", "source", 3) 
		&& filtered.size() == 1);

	clearFiles();
}


void CoatServiceConstructors_ValidConstructors()
{
	//CoatService service;
	//CoatService srv = service;
	//service = service;

	//assert(service.listCoats().size() == 0);
}

void CoatServiceGetNextFromCoatService_RepositoryWithOneElement_FirstElement()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);

	service.storeCoatService("name", "size", "source", "3");
	service.setCoatIteratorToFirst();

	assert(service.getNextCoatFromIterator().to_string() == TrenchCoat("name", "size", "source", 3).to_string());
	clearFiles();
}

void CoatServiceEmptyUserList_UserListWithOneElement_EmptyList()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	service.setUserRepositoryPath(UserListTestFileCSV);

	service.storeCoatService("name", "size", "source", "3");

	service.saveTrenchCoatToUserList("name");

	service.emptyUserCoats();
	assert(service.getUserCoats().size() == 0);

	clearFiles();

}

void CoatServiceUpdateCoat_UserListWithOneElement_UpdatedCoatInUserList()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	service.setUserRepositoryPath(UserListTestFileCSV);
	service.storeCoatService("name", "size", "source", "3");

	service.saveTrenchCoatToUserList("name");
	service.updateCoatService("name", "size2", "source2", "5");

	std::vector<TrenchCoat> userCoats{ service.getUserCoats() };
	assert(userCoats[0].to_string() == TrenchCoat("name", "size2", "source2", 5).to_string());

	clearFiles();

}

void CoatServiceSetPath_HTMlrepository_CorrectRepository()
{
	CoatService service{};
	service.setCoatRepositoryPath(TestFile);
	service.setUserRepositoryPath(UserListTestFileHTML);

	service.storeCoatService("name", "size", "source", "3");
	service.saveTrenchCoatToUserList("name");

	std::ifstream fin{ UserListTestFileHTML };

	std::string string;
	std::getline(fin, string);

	assert(string == "<!DOCTYPE html>");
	
	fin.close();
	clearFiles();
}

void test_CoatService()
{
	CoatServiceStoreCoat_ValidCoat_CoatAdded();
	CoatServiceStoreCoat_InvalidCoat_CoatNotAdded();
	CoatServiceDeleteCoat_ValidCoat_CoatDeleted();
	CoatServiceDeleteCoat_InvalidCoat_CoatNotDeleted();
	CoatServiceUpdateCoat_ValidCoat_UpdatedCoat();
	CoatServiceUpdateCoat_InexistentCoat_Exception();
	CoatServiceSaveTrenchCoatToUserList_ValidCoat_CoatAdded();
	CoatServiceListFilteredCoats_ThreeCoats_OneCoatAfterFilter();
	CoatServiceConstructors_ValidConstructors();
	CoatServiceStoreCoat_InvalidCoatPrice_ExceptionRaised();
	CoatServiceUpdateCoat_InvalidCoatPrice_ExceptionRaised();
	CoatServiceConstructors_ValidConstructors();
	CoatServiceGetNextFromCoatService_RepositoryWithOneElement_FirstElement();
	CoatServiceEmptyUserList_UserListWithOneElement_EmptyList();
	CoatServiceDeleteCoat_UserListWithOneCoat_DeletesTheCoatFromUserList();
	CoatServiceSetPath_HTMlrepository_CorrectRepository();
	CoatServiceUpdateCoat_UserListWithOneElement_UpdatedCoatInUserList();
}


void CoatsIteratorGetCurrent_DynamicVectorWithOneElement_CorrectElement()
{
	TrenchCoat coat{ "a","a","a",1 };
	std::vector<TrenchCoat> dynVector;
	dynVector.push_back(coat);

	CoatsIterator iterator{ dynVector };

	assert(iterator.getCurrent() == coat);
}

void CoatsIteratorNext_DynamicVectorWithTwoElements_CorrectSecondElement()
{
	TrenchCoat coat1{ "a","a","a",1 };
	TrenchCoat coat2{ "b","a","a",1 };
	std::vector<TrenchCoat> dynVector;
	dynVector.push_back(coat1);
	dynVector.push_back(coat2);

	CoatsIterator iterator{ dynVector };
	iterator.next();

	assert(iterator.getCurrent() == coat2);
}

void CoatsIteratorNext_DynamicVectorWithTwoElements_LoopsBack()
{
	TrenchCoat coat1{ "a","a","a",1 };
	TrenchCoat coat2{ "b","a","a",1 };
	std:: vector<TrenchCoat> dynVector;
	dynVector.push_back(coat1);
	dynVector.push_back(coat2);

	CoatsIterator iterator{ dynVector };
	iterator.next();
	iterator.next();

	assert(iterator.getCurrent() == coat1);
}

void CoatsIteratorConstructor_SameConstructor_IteratorCopied()
{
	std::vector<TrenchCoat> coats;
	CoatsIterator iterator{ coats }, iterator2{};
	CoatsIterator iter = iterator;
	iterator = iterator;
	iterator = iterator2;
	assert(iterator.valid() == false);
}

void test_CoatsIterator()
{
	CoatsIteratorGetCurrent_DynamicVectorWithOneElement_CorrectElement();
	CoatsIteratorNext_DynamicVectorWithTwoElements_CorrectSecondElement();
	CoatsIteratorNext_DynamicVectorWithTwoElements_LoopsBack();
	CoatsIteratorConstructor_SameConstructor_IteratorCopied();
}

void tokenize_String_SplitString()
{
	std::string stringToBeSplit{" , ,,,   abc ,, , , 123 , , , "};
	std::vector<std::string> splitString{ tokenize(stringToBeSplit, ',') };
	assert(splitString[0].compare("abc") == 0 
		&& splitString[1].compare("123") == 0);
}

void tokenize_stringWithourDelimiter_SplitStringWithRespectToSpaces()
{
	std::string stringToBeSplit{ "    abc    123    " };
	std::vector<std::string> splitString{ tokenize(stringToBeSplit, ',') };
	assert(splitString[0].compare("abc") == 0
		&& splitString[1].compare("123") == 0);
}

void Exceptions_Message_CorrectMessage()
{
	try
	{
		throw Exceptions("message");
	}
	catch (Exceptions & exception)
	{
		assert(strcmp(exception.what(), "message") == 0);
	}
}

void CoatValidatorValidateName_EmptyName_ErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validateName("").size() != 0);
}

void CoatValidatorValidateName_NonEmptyName_NoErrorMessage()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validateName("name").size() == 0);
}

void CoatValidatorValidateSize_EmptySize_ErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validateSize("").size() != 0);
}

void CoatValidatorValidateSize_NonEmptySize_NoErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validateSize("size").size() == 0);
}

void CoatValidatorValidateSource_EmptySource_ErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validatePhotographSource("").size() != 0);
}

void CoatValidatorValidateSource_NonEmptySource_NoErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validatePhotographSource("source").size() == 0);
}

void CoatValidatorValidatePrice_EmptyPrice_ErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validatePrice("").size() != 0);
}

void CoatValidatorValidatePrice_NonNaturalNumber_ErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validatePrice("price").size() != 0);
}

void CoatValidatorValidatePrice_NaturalNumber_NoErrorMessageReturned()
{
	CoatValidator coatsValidator;
	assert(coatsValidator.validatePrice("3").size() == 0);
}

void CoatValidatorValidateCoat_ValidCoat_NoExceptionThrown()
{
	CoatValidator coatsValidator;
	coatsValidator.validateCoat("name", "size", "source", "4");
}

void CoatValidatorValidateCoat_InValidCoatFields_InvalidCoatExceptionThrown()
{
	CoatValidator coatsValidator;
	try
	{
	coatsValidator.validateCoat("", "", "", "asd4");
	assert(false);
	}
	catch(InvalidCoat&)
	{
		assert(true);
	}
}

void test_CoatValidator()
{
	CoatValidatorValidateCoat_ValidCoat_NoExceptionThrown();
	CoatValidatorValidatePrice_NonNaturalNumber_ErrorMessageReturned();
	CoatValidatorValidatePrice_NaturalNumber_NoErrorMessageReturned();
	CoatValidatorValidatePrice_EmptyPrice_ErrorMessageReturned();
	CoatValidatorValidateSource_NonEmptySource_NoErrorMessageReturned();
	CoatValidatorValidateSource_EmptySource_ErrorMessageReturned();
	CoatValidatorValidateName_EmptyName_ErrorMessageReturned();
	CoatValidatorValidateName_NonEmptyName_NoErrorMessage();
	CoatValidatorValidateSize_EmptySize_ErrorMessageReturned();
	CoatValidatorValidateSize_NonEmptySize_NoErrorMessageReturned();
	CoatValidatorValidateCoat_InValidCoatFields_InvalidCoatExceptionThrown();
}

void testAll()
{
	test_TrenchCoat();
	test_CoatService();
	test_CoatsIterator();
	test_FileRepository();  
	tokenize_String_SplitString();
	Exceptions_Message_CorrectMessage();
	tokenize_stringWithourDelimiter_SplitStringWithRespectToSpaces();
	test_CoatValidator();
	
}

