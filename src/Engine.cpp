/*
 **
 ** Made by Applelo
 **
 */

# include "../include/Engine.hh"

Engine::Engine() {
	_setup = this->calcSetup();
}

Engine::~Engine() {
}

int Engine::auto_switch() {
		if (_setup == UMA0)
			return this->switch_to_ux0();
		else
			return this->switch_to_uma0();
}


int Engine::switch_to_ux0() {
	//remove old installation if exist
	//_file = new File(UMA0_LOCALIZATION);
	//if (_file->checkFileExist())
	//	_file->removeFile();
	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("\n" UMA0_LOCALIZATION) > 0)
		_file->deleteFileLine("\n" UMA0_LOCALIZATION, _file->findFileLine("\n" UMA0_LOCALIZATION));


	_file = new File(UX0_LOCALIZATION);

	if ( !_file->checkFileExist() ) {

		delete _file;

		//copy ux0 plugin
		_file = new File(UX0_APP_LOCALIZATION);

		if (_file->checkFileExist()) {
			_result = _file->copyFile(UX0_LOCALIZATION, NULL);
			if (!_result)
				return 0;
		}
		else {
			return 0;
		}
	}

	delete _file;



	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("*KERNEL") < 0)
		return 0;
	if (_file->findFileLine("\n" UX0_LOCALIZATION) > 0)
		return 0;

	_file->addFileLine("\n" UX0_LOCALIZATION, _file->findFileLine("*KERNEL"));
	delete _file;

	_setup = UX0;
	return 1;
}

int Engine::switch_to_uma0() {
	//remove old installation if exist
	// _file = new File(UX0_LOCALIZATION);
	// if (_file->checkFileExist())
	// 	_file->removeFile();
	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("\n" UX0_LOCALIZATION) > 0)
		_file->deleteFileLine("\n" UX0_LOCALIZATION, _file->findFileLine("\n" UX0_LOCALIZATION));

	delete _file;


	_file = new File(UMA0_LOCALIZATION);

	if ( !_file->checkFileExist() ) {

		delete _file;

		//copy uma0 plugin
		_file = new File(UMA0_APP_LOCALIZATION);

		if (_file->checkFileExist()) {
			_result = _file->copyFile(UMA0_LOCALIZATION, NULL);
			if (!_result)
				return 0;
		}
		else {
			return 0;
		}
	}

	delete _file;


	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("*KERNEL") < 0)
		return 0;
	if (_file->findFileLine("\n" UMA0_LOCALIZATION) > 0)
		return 0;

	_file->addFileLine("\n" UMA0_LOCALIZATION, _file->findFileLine("*KERNEL"));

	_setup = UMA0;
	return 1;
}

int Engine::uninstall() {
	//Remove plugin
	// _file = new File(UX0_LOCALIZATION);
	// if (_file->checkFileExist())
	// 	_file->removeFile();
	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("\n" UX0_LOCALIZATION) > 0)
		_file->deleteFileLine("\n" UX0_LOCALIZATION, _file->findFileLine("\n" UX0_LOCALIZATION));



	// _file = new File(UMA0_LOCALIZATION);
	// if (_file->checkFileExist())
	// 	_file->removeFile();
	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("\n" UMA0_LOCALIZATION) > 0)
		_file->deleteFileLine("\n" UMA0_LOCALIZATION, _file->findFileLine("\n" UMA0_LOCALIZATION));

	//Uninstall old installation
	if (this->isOldInstallation()) {
		_file = new File(OLD_CONFIG_LOCALIZATION);
		if (_file->findFileLine("\n" UMA0_LOCALIZATION) > 0)
			_file->deleteFileLine("\n" UMA0_LOCALIZATION, _file->findFileLine("\n" UMA0_LOCALIZATION));
	}
	_setup = NO;
	return 1;
}

//Setter
void Engine::setSetup(const Setup setup) {
	_setup = setup;
}

//Getter
const Setup Engine::getSetup() {
	return _setup;
}

const Setup Engine::calcSetup() {
	_setup = NO;

	_file = new File(CONFIG_LOCALIZATION);

	if ( !_file->checkFileExist() )
		return _setup;

	if (_file->findFileLine("\n" UX0_LOCALIZATION) > 0)
		_setup = UX0;

	else if (_file->findFileLine("\n" UMA0_LOCALIZATION) > 0)
		_setup = UMA0;

	return _setup;
}

const bool Engine::isOldInstallation() {
	_file = new File(OLD_CONFIG_LOCALIZATION);
	if (!_file->checkFileExist())
		return false;

	if (_file->findFileLine(UMA0_LOCALIZATION) > 0)
		return true;
	return false;
}

void Engine::reboot() {
	scePowerRequestColdReset();
}

void Engine::installChangelog() {
	sceIoMkdir("ux0:patch/SWITCHSDV/", 0777);//Create folders for if it doesn't exist
	sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/", 0777);
	sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/changeinfo", 0777);
	_file = new File(CHANGELOG_LOCALIZATION);
	_file->copyFile(NEW_CHANGELOG_LOCALIZATION, NULL);
}
