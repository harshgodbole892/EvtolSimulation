/*
 
 Hierarchy     : EvtolSimulation
 Model         : N/A
 Function Name : main
 Function Type : Dynamic Dispatcher
 */

//Tempelate by Harsh Godbole.

// Generic includes:
#include <iostream>
#include <armadillo>
#include <vector>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include <gtest/gtest.h>

// Project Specific includes:
#include "LocalSharedMemory.hpp"
#include "SimDispatcher.hpp"
#include "CommonDefines.hpp"
#include "SimComponent.hpp"
#include "Vehicle.hpp"
#include "ChargingQueue.hpp"
#include "Observer.hpp"



using namespace std;

// The fixture for testing class Foo.
class TestableVehicle : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
    TestableVehicle() {
        
        // Check that getenv has not returned a NULL pointer:
        const char *wProjectHomeDirPtr = getenv("PROJECT_HOME_DIR");
        if (!wProjectHomeDirPtr)
        {
             mProjectHomeDir.assign("//");
             cout<<"Env Variable PROJECT_HOME_DIR is not set, Use RunFile to execute tests"<<endl;
        }
        
        mProjectHomeDir.assign(wProjectHomeDirPtr);
  }

  ~TestableVehicle() override {
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
      // Code here will be called immediately after the constructor (right
      // before each test).
      mLSMPtr           = new LocalSharedMemory(mProjectHomeDir);
      mVehicleAlphaPtr  = new Vehicle(1, "Alpha", *mLSMPtr);
      mVehicleBetaPtr   = new Vehicle(2, "Beta",  *mLSMPtr);
      
      mVehicleAlphaPtr->setCollectSize(mCollectSize);
      mVehicleBetaPtr->setCollectSize(mCollectSize);
  
  }

  void TearDown() override {
      // Code here will be called immediately after each test (right
      // before the destructor).
      delete mVehicleAlphaPtr;
      delete mVehicleBetaPtr;
      delete mLSMPtr;
  }
    
    Vehicle           *mVehicleAlphaPtr = NULL;
    Vehicle           *mVehicleBetaPtr  = NULL;
    LocalSharedMemory *mLSMPtr = NULL;
    
    string mProjectHomeDir;
    int mCollectSize = 1080;
    
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(TestableVehicle, CheckInitialization) {

    EXPECT_EQ(mVehicleAlphaPtr->getCollectSize(), mCollectSize);
    EXPECT_EQ(mVehicleBetaPtr->getCollectSize(), mCollectSize);
    
    // Run the initialization:
    mLSMPtr->setIterationIndex(0);
    
    // Set init mode:
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::CRUISE_FULLBAT);
    
    // Call update
    mVehicleAlphaPtr->update(*mLSMPtr);
    mVehicleBetaPtr->update(*mLSMPtr);
    
    // Check states:
    EXPECT_EQ(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr), mVehicleAlphaPtr->getBatteryCapacity());
    EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::CRUISE);

    // Set init mode
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::DISCHARGED_EMPTYBATT);
    
    // Call Update
    mVehicleAlphaPtr->update(*mLSMPtr);
    mVehicleBetaPtr->update(*mLSMPtr);
    
    // Check Init modes
    EXPECT_EQ(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) ,0.0);
    EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::DISCHARGED);
    
    // Set init mode
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::QUEUE_EMPTYBATT);
    
    // Call Update
    mVehicleAlphaPtr->update(*mLSMPtr);
    mVehicleBetaPtr->update(*mLSMPtr);
    
    // Check Init modes
    EXPECT_EQ(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) ,0.0);
    EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::QUEUE);
    
    // Set init mode
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::CHARGING_EMPTYBATT);
    
    // Call Update
    mVehicleAlphaPtr->update(*mLSMPtr);
    mVehicleBetaPtr->update(*mLSMPtr);
    
    // Check Init modes
    EXPECT_EQ(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) ,0.0);
    EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::CHARGING);
    
}

TEST_F(TestableVehicle, CheckCruiseTransitionAndBatteryDrain) {
    
    // Set init mode:
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::CRUISE_FULLBAT);
    
    // Run the initialization:
    mLSMPtr->setIterationIndex(0);
    
    // Initialize:
    mLSMPtr->setIterationIndex(0);
    mVehicleAlphaPtr->update(*mLSMPtr);
    
    double wTempBatteryCharge = mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr);
    
    // Start looping
    for (int i=1; i < mCollectSize; i++)
    {
        mLSMPtr->setIterationIndex(i);
        mVehicleAlphaPtr->update(*mLSMPtr);
             
        // If discharged
        if(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) < 0.0)
        {
            // Should be discharged if battery is lost
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::DISCHARGED);
        }
        else
        {
            // Should lose battery if in cruise
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::CRUISE);
            EXPECT_TRUE(wTempBatteryCharge > mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr));
        }
        wTempBatteryCharge = mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr);
    }
}

TEST_F(TestableVehicle, CheckQueueTransition) {
    
    // Set init mode:
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::DISCHARGED_EMPTYBATT);
    
    // Run the initialization:
    mLSMPtr->setIterationIndex(0);
    
    for (int i=0; i < mCollectSize; i++)
    {
        mLSMPtr->setIterationIndex(i);
        mVehicleAlphaPtr->update(*mLSMPtr);
        
        // Send queue trigger to the vehicle
        if ( (i > 5) && (mVehicleAlphaPtr->getVehicleState(*mLSMPtr) == DISCHARGED))
        {
            mVehicleAlphaPtr->setVehicleState(VehicleState::QUEUE, *mLSMPtr);
        }
        
        if( i > 5)
        {
            // Should stay in queue until charging
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::QUEUE);
        }
        else
        {
            // Should stay discharged
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::DISCHARGED);
        }
        
    }
}

TEST_F(TestableVehicle, CheckChargingTransition) {
    
    // Set init mode:
    mVehicleAlphaPtr->setVehicleInitMode(VehicleInitMode::QUEUE_EMPTYBATT);
    
    // Run the initialization:
    mLSMPtr->setIterationIndex(0);
    
    // Initialize:
    mLSMPtr->setIterationIndex(0);
    mVehicleAlphaPtr->update(*mLSMPtr);
    
    int wCounter = 0;
    
    for (int i=1; i < mCollectSize; i++)
    {
        // Initialize
        mLSMPtr->setIterationIndex(i);
        mVehicleAlphaPtr->update(*mLSMPtr);
        
        // Send charging trigger to the vehicle
        
        if ( (i > 5) && (mVehicleAlphaPtr->getVehicleState(*mLSMPtr) == VehicleState::QUEUE))
        {
            mVehicleAlphaPtr->setVehicleState(VehicleState::CHARGING, *mLSMPtr);
        }
        
        // Check if it stays in charging
        if((mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) > 0.0))
        {
            // Should stay Cruise
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::CRUISE);
            
            // Break before going back to queue state
            wCounter++;
            if (wCounter > 10) break;
        }
        else if ( !(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) > 0.0) && (i <= 5) )
        {
            // Should stay in Queue
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::QUEUE);
        }
        else if ( !(mVehicleAlphaPtr->getBatteryCharge(*mLSMPtr) > 0.0))
        {
            // Should stay in charging
            EXPECT_EQ(mVehicleAlphaPtr->getVehicleState(*mLSMPtr), VehicleState::CHARGING);
        }
        
    }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
    
  return RUN_ALL_TESTS();
}

// End of Main
