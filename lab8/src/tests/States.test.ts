import {
    beforeEach,
    describe,
    expect,
    test,
} from '@jest/globals'
import {
    IGumballMachine,
    NoQuarterState,
    HasQuarterState,
    SoldOutState,
    SoldState,
} from '../GumballMachine'

const createMockGumballMachine = (): jest.Mocked<IGumballMachine> => ({
    ReleaseBall: jest.fn(),
    AddQuarter: jest.fn(),
    RemoveAllQuarters: jest.fn(),
    RemoveOneQuarter: jest.fn(),
    GetBallCount: jest.fn(),
    GetQuarterCount: jest.fn(),
    GetState: jest.fn(),
    
    SetSoldOutState: jest.fn(),
    SetNoQuarterState: jest.fn(),
    SetSoldState: jest.fn(),
    SetHasQuarterState: jest.fn(),
})

describe('NoQuarterState', () => {
    let mockMachine: jest.Mocked<IGumballMachine>
    let state: NoQuarterState

    beforeEach(() => {
        mockMachine = createMockGumballMachine()
        state = new NoQuarterState(mockMachine)
    })

    test('InsertQuarter should add a quarter and change to HasQuarterState', () => {
        state.InsertQuarter()
        expect(mockMachine.AddQuarter).toHaveBeenCalled()
        expect(mockMachine.SetHasQuarterState).toHaveBeenCalled()
    })

    test('EjectQuarter should do nothing', () => {
        state.EjectQuarter()
        expect(mockMachine.RemoveOneQuarter).not.toHaveBeenCalled()
    })

    test('TurnCrank should do nothing', () => {
        state.TurnCrank()
        expect(mockMachine.SetSoldState).not.toHaveBeenCalled()
        expect(mockMachine.ReleaseBall).not.toHaveBeenCalled()
    })

    test('Dispense should do nothing', () => {
        state.Dispense()
        expect(mockMachine.ReleaseBall).not.toHaveBeenCalled()
    })
})

describe('HasQuarterState', () => {
    let mockMachine: jest.Mocked<IGumballMachine>
    let state: HasQuarterState

    beforeEach(() => {
        mockMachine = createMockGumballMachine()
        mockMachine.GetQuarterCount.mockReturnValue(1)
        state = new HasQuarterState(mockMachine)
    })

    test('InsertQuarter should add a quarter if under limit', () => {
        mockMachine.GetQuarterCount.mockReturnValue(4)
        state.InsertQuarter()
        expect(mockMachine.AddQuarter).toHaveBeenCalled()
    })

    test('InsertQuarter should not add a quarter if at limit', () => {
        mockMachine.GetQuarterCount.mockReturnValue(5)
        state.InsertQuarter()
        expect(mockMachine.AddQuarter).not.toHaveBeenCalled()
    })

    test('TurnCrank should change to SoldState and decrement quarter count', () => {
        state.TurnCrank()
        expect(mockMachine.SetSoldState).toHaveBeenCalled()
        expect(mockMachine.RemoveOneQuarter).toHaveBeenCalled()
    })

    test('Dispense should do nothing', () => {
        state.Dispense()
        expect(mockMachine.ReleaseBall).not.toHaveBeenCalled()
    })
})

describe('SoldState', () => {
    let mockMachine: jest.Mocked<IGumballMachine>
    let state: SoldState

    beforeEach(() => {
        mockMachine = createMockGumballMachine()
        state = new SoldState(mockMachine)
    })

    test('InsertQuarter should not allow inserting a quarter', () => {
        state.InsertQuarter()
        expect(mockMachine.AddQuarter).not.toHaveBeenCalled()
    })

    test('EjectQuarter should return a quarter if present', () => {
        mockMachine.GetQuarterCount.mockReturnValue(1)
        state.EjectQuarter()
        expect(mockMachine.RemoveOneQuarter).toHaveBeenCalled()
    })

    test('TurnCrank should not allow turning twice', () => {
        state.TurnCrank()
        expect(mockMachine.ReleaseBall).not.toHaveBeenCalled()
    })

    test('Dispense should release a ball and adjust state based on inventory', () => {
        mockMachine.GetBallCount.mockReturnValue(1)
        state.Dispense()
        expect(mockMachine.ReleaseBall).toHaveBeenCalled()
        expect(mockMachine.SetNoQuarterState).toHaveBeenCalled()

        mockMachine.GetBallCount.mockReturnValue(0)
        state.Dispense()
        expect(mockMachine.SetSoldOutState).toHaveBeenCalled()
    })
})

describe('SoldOutState', () => {
    let mockMachine: jest.Mocked<IGumballMachine>
    let state: SoldOutState

    beforeEach(() => {
        mockMachine = createMockGumballMachine()
        state = new SoldOutState(mockMachine)
    })

    test('InsertQuarter should not allow adding quarters', () => {
        state.InsertQuarter()
        expect(mockMachine.AddQuarter).not.toHaveBeenCalled()
    })

    test('EjectQuarter should return all quarters', () => {
        mockMachine.GetQuarterCount.mockReturnValue(3)
        state.EjectQuarter()
        expect(mockMachine.RemoveAllQuarters).toHaveBeenCalled()
    })

    test('TurnCrank should do nothing', () => {
        state.TurnCrank()
        expect(mockMachine.SetSoldState).not.toHaveBeenCalled()
    })

    test('Dispense should not dispense any gumballs', () => {
        state.Dispense()
        expect(mockMachine.ReleaseBall).not.toHaveBeenCalled()
    })
})
