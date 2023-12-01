class SeatManager
{
private:
    int seats[2];
    int lowest;
    int n;

public:
    SeatManager(int n)
    {
        // this->seats = new int[n];

        for (int i = 0; i < n; i++)
            this->seats[i] = i;

        this->n = n;
        this->lowest = 1;
    }

    int reserve()
    {
        this->seats[this->lowest - 1] = -1;

        int tmp = this->lowest;

        for (int i = this->lowest; i < this->n; i++)
            if (this->seats[i] == i)
            {
                this->lowest = i + 1;
                break;
            }

        this->lowest == tmp ? this->lowest = INT_MAX : this->lowest;

        return tmp;
    }

    void unreserve(int seatNumber)
    {

        if (this->lowest > seatNumber)
            this->lowest = seatNumber;

        this->seats[seatNumber - 1] = seatNumber - 1;
    }
};
