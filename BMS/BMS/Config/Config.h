#ifndef CONFIG_H_
#define CONFIG_H_

#include <QString>

// 本地配置文件...
class Config {
private:
	Config();
	~Config();
	Config(const Config& ref) {}
	Config& operator=(const Config& ref) {}
	static Config* _instance;

public:
	struct ConfigSpeech {
		int powerState_;      // 语音开关状态 0:关闭 1:打开
		int volume_;          // 音量...
		QString content_;     // 播报内容...
	};

public:
	static Config* GetInstance();

public:
	void SetConfigSpeech(ConfigSpeech configSpeech);
	ConfigSpeech GetConfigSpeech();

public:
	void LoadConfigFile();
	void SaveConfigFile();

private:
	ConfigSpeech _configSpeech;
};

#endif // !CONFIG_H_