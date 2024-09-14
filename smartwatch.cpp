#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

using ::testing::Return;
using ::testing::_;

class Connection {

public:
	virtual void setConnection() = 0;
	virtual int connect(int timeout) = 0;
};

class MockConnection: public Connection {

public: 
	MOCK_METHOD(void, setConnection, (), (override));
	MOCK_METHOD(int, connect, (int timeout), (override));
	
};

class SmartWatch {
	Connection& conn;

public:

	enum BatteryState {
		LOW,
		MEDIUM,
		HIGH
	};

	SmartWatch(Connection& conn): conn{conn} {}

	void openBrowser(){
		this->conn.setConnection();
		this->conn.connect(1);
	}

	BatteryState checkbattery(){
		return BatteryState::HIGH;
	}

};

TEST(SmartWatchTest, ConnectionTest) {
	MockConnection connection; 
	EXPECT_CALL(connection, connect(_)).Times(1).WillOnce(Return(1));

	SmartWatch watch(connection);
	watch.openBrowser();

}

TEST(SmartWatchTest, BatteryLevelTest){
	MockConnection connection; 
	SmartWatch watch(connection);
	EXPECT_EQ(watch.checkbattery(), SmartWatch::BatteryState::HIGH);
}
