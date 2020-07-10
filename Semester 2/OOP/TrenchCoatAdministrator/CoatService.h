#pragma once
#include "FileRepository.h"
#include "CoatsIterator.h"
#include "FileRepository.h"
#include "CoatValidator.h"
#include "Action.h"
#include "InMemoryRepository.h"
#include "Observer.h"
#include <memory>

class CoatService: public Observable
{
private:
	AbstractRepository* coatRepository;
	CoatsIterator coatsIterator;
	CoatValidator* coatsValidator;
	AbstractRepository* userRepository;

	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;


	std::vector<std::unique_ptr<Action>> userUndoStack;
	std::vector<std::unique_ptr<Action>> userRedoStack;

	bool duringUndo = false, duringUserUndo = false;

public:
	CoatService() :coatRepository{ new CSVFileRepository }, coatsValidator { new CoatValidator }, userRepository{ new CSVFileRepository }, duringUndo{ false } {}

	CoatService(CSVFileRepository& coatRepository, CoatValidator* coatsValidator);

	CoatService(CSVFileRepository& coatRepository);

	CoatService(const CoatService& coatService);

	CoatService& operator=(const CoatService& coatService);

	~CoatService();

	//raises an exception if coat fields are invalid
	void storeCoatService(const std::string& name, const std::string& size, const std::string& photographSource, const std::string& price);

	void deleteCoatService(const std::string name);

	//raises an exception if coat fields are invalid
	void updateCoatService(const std::string& name, const std::string& size, const std::string& photographSource, const std::string& price);

	std::vector<TrenchCoat> listCoats();

	TrenchCoat getCoatFromRepository(int position);

	TrenchCoat getCoatFromUserRepository(int position);

	int getRepositoryLength();

	int getUserRepositoryLength();

	//returns an interator over the list of coats
	CoatsIterator getCoatsIterator();

	void setCoatsIterator();

	void saveTrenchCoatToUserList(const std::string& name);

	std::vector<TrenchCoat> listFilteredCoats(const std::string& size, const std::string& price);

	std::vector<TrenchCoat> getUserCoats();

	void emptyUserCoats();

	void setCoatIteratorToFirst();

	TrenchCoat getNextCoatFromIterator();

	void setPath(const std::string& filePath, const std::string& userRepositoryPath = "");

	void setCoatRepositoryPath(const std::string& filePath);

	void setUserRepositoryPath(const std::string& userRepositoryPath);

	void openUserFile();

	void undo();
	void redo();

	void undoUser();
	void redoUser();
};

