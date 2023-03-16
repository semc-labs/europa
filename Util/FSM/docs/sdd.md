\page UtilsFSM Utils::FSM Component
# Utils::FSM Component

## 1 Introduction

## 2 Requirements

Requirement | Description | Rationale | Verification Method
---- | ---- | ---- | ----
FSM-001 | Invalid state transitions must be prevented, and an error thrown | Prevent invalid transitions | Unit Test

## 3 Design

### 3.1 Assumptions

### 3.3 Ports

#### 3.3.1 Role Ports

Name | Type | Role
---- | ---- | ----
`cmdIn` | `Fw::Cmd` | Cmd
`cmdRegOut` | `Fw::CmdReg` | CmdReg
`cmdResponseOut` | `Fw::CmdResponse` | CmdResponse
`eventOut` | `Fw::Log` | Event
`textEventOut` | `Fw::LogText` | TextEvent
`tlmOut` | `Fw::Tlm` | Tlm
`timeGetOut` | `Fw::Time` | Time

#### 3.3.2 Component-Specific Ports

Name | Type | Kind | Purpose
---- | ---- | ---- | ----
`getState` | `state: U8` | sync input | Returns the current state
`onTransition` | `state: U8` | output | Signal when the state changes
`transistion` | `newState: U8` | sync input | Triggers a state transition

### 3.4 Constants

Name | Type | Purpose
---- | ---- | ----
`transitions` | `U16[][] = {{curState, newState}}` | Represent valid state transistions

### 3.5 Commands

Name | Parameters | Kind | Purpose
---- | ---- | ---- | ---- 
`Transition` | `transitionId: U16` | sync | Initiate a state transition

### 3.6 Events

Name | Parameters | Severity | Purpose
---- | ---- | ---- | ----
`Transition` | `transitionId: U16` | `activity high` | Log state transitions
`InvalidTransition` | `transitionId: U16` | `warning high` | Warning when an invalid transition is requested

### 3.7 Telemetry

Name | Type | Purpose
---- | ---- | ----
`CurrentState` | `state: U8` | Indicate current state

## 6 Unit Tests
