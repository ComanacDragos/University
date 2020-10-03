public class NumarComplex {
    double re, im;

    public NumarComplex(double re, double im)
    {
        this.re = re;
        this.im = im;
    }

    public NumarComplex adunare(NumarComplex nr)
    {
        return new NumarComplex(this.re + nr.re, this.im + nr.im);
    }

    public NumarComplex scadere(NumarComplex nr)
    {
        return new NumarComplex(this.re - nr.re, this.im - nr.im);
    }

    public NumarComplex inmultire(NumarComplex nr)
    {
        return new NumarComplex(this.re * nr.re - this.im * nr.im, this.re * nr.im + this.im * nr.re);
    }

    public NumarComplex impartire(NumarComplex nr)
    {
        return new NumarComplex((this.re * nr.re + this.im * nr.im) / (Math.pow(nr.re, 2) + Math.pow(nr.im, 2)),
                                (this.im * nr.re-this.re * nr.im) / (Math.pow(nr.re, 2) + Math.pow(nr.im, 2)));
    }

    public NumarComplex conjugat()
    {
        return new NumarComplex(this.re, -this.im);
    }

    @Override
    public String toString() {
        return Double.toString(this.re) + ", " + Double.toString(this.im) ;
    }
}
