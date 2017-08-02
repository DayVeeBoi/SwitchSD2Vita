/*
 **
 ** Made by Applelo
 **
 */

# include "../include/Engine.hh"


Engine::Engine() {
	int _result;
}

Engine::~Engine() {
}

int Engine::switch_to_ux0() {
	//remove old installation if exist
	_file = new File("ur0:tai/gamesd_uma0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	//copy ux0 plugin
	_file = new File("app0:plugins/gamesd_ux0.skprx");
	_result = _file->copyFile("ur0:tai/gamesd_ux0.skprx", NULL);
	if (!_result)
		return 0;

	//_console->pushLog("Copied!");
	return 1;
}

int Engine::switch_to_uma0() {
	//remove old installation if exist
	_file = new File("ur0:tai/gamesd_ux0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	//copy uma0 plugin
	_file = new File("app0:plugins/gamesd_uma0.skprx");
	_result = _file->copyFile("ur0:tai/gamesd_uma0.skprx", NULL);
	if (!_result)
		return 0;

	return 1;
}

int Engine::uninstall() {

	_file = new File("ur0:tai/gamesd_ux0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	_file = new File("ur0:tai/gamesd_uma0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	//uint8_t *buffer = malloc(BIG_BUFFER_SIZE);

	//_file = new File("ur0:/tai/config.txt");
	//_file->readFile(buffer, BIG_BUFFER_SIZE);
	return 1;
}