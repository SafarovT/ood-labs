enum State {
    SoldOut = 'SoldOut',
    NoQuarter = 'NoQuarter',
    HasQuarter = 'HasQuarter',
    Sold = 'Sold',
}

class GumballMachine {
    private count: number
    private quarters: number
    private readonly maxQuarters: number = 5
    private state: State

    constructor(count: number) {
        this.count = count
        this.quarters = 0
        this.state = count > 0 ? State.NoQuarter : State.SoldOut
    }

    InsertQuarter(): void {
        if (this.quarters >= this.maxQuarters) {
            console.log("You can't insert more quarters, the machine is full")
            return
        }
        switch (this.state) {
            case State.SoldOut:
                console.log("You can't insert a quarter, the machine is sold out")
                break
            case State.NoQuarter:
            case State.HasQuarter:
                this.quarters++
                console.log(`You inserted a quarter. Total quarters: ${this.quarters}`)
                this.state = State.HasQuarter
                break
            case State.Sold:
                console.log("Please wait, we're already giving you a gumball")
                break
        }
    }

    EjectQuarter(): void {
        if (this.quarters > 0) {
            let queartesBefore = this.quarters
            if (this.state === State.SoldOut) {
                this.quarters = 0
                this.state = this.count > 0
                    ? State.NoQuarter
                    : State.SoldOut
            }
            else {
                this.quarters--
                if (!this.quarters) {
                    this.state = State.NoQuarter
                } 
            }
            console.log(`Quarters returned: ${queartesBefore - this.quarters}`)
           
        }
        else {
            console.log("You haven't inserted any quarters")
        }
    }

    TurnCrank(): void {
        switch (this.state) {
            case State.SoldOut:
                console.log("You turned but there's no gumballs")
                break
            case State.NoQuarter:
                console.log("You turned but there's no quarter")
                break
            case State.HasQuarter:
                console.log("You turned...")
                this.state = State.Sold
                this.Dispense()
                break
            case State.Sold:
                console.log("Turning twice doesn't get you another gumball")
                break
        }
    }

    Refill(numBalls: number): void {
        this.count += numBalls
        console.log(`Machine refilled. New inventory: ${this.count}`)
        if (this.count > 0 && !this.quarters) {
            this.state = State.NoQuarter
        }
        else if (this.count > 0 && this.quarters > 0) {
            this.state = State.HasQuarter
        }
    }

    ToString(): string {
        const stateDescription = this.state === State.SoldOut
            ? "sold out"
            : this.state === State.NoQuarter
                ? "waiting for quarter"
                : this.state === State.HasQuarter
                    ? "waiting for turn of crank"
                    : "delivering a gumball"

        return `
Mighty Gumball, Inc.
TS-enabled Standing Gumball Model
Inventory: ${this.count} gumball${this.count !== 1 ? "s" : ""}
Quarters: ${this.quarters}
Machine is ${stateDescription}
`
    }

    private Dispense(): void {
        if (this.quarters > 0 && this.count > 0) {
            console.log("A gumball comes rolling out the slot")
            this.quarters--
            this.count--
            if (!this.count) {
                console.log("Oops, out of gumballs")
                this.state = State.SoldOut
            }
            else if (!this.quarters) {
                this.state = State.NoQuarter
            }
            else {
                this.state = State.HasQuarter
            }
        }
        else if (this.quarters > 0 && !this.count) {
            console.log("No gumball dispensed, returning quarters...")
            this.EjectQuarter()
        }
        else {
            console.log("You need to pay first")
        }
    }
}

export {
    GumballMachine,
}