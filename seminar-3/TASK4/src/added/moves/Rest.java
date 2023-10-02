package added.moves;
import ru.ifmo.se.pokemon.*;
public class Rest extends StatusMove{
    public Rest(){
        super(Type.PSYCHIC, 0, 100);
    }
    @Override
    protected void applySelfEffects(Pokemon p){
        Effect e = new Effect().condition(Status.SLEEP).turns(2);
        p.addEffect(e);
        Effect e1 = new Effect().stat(Stat.HP, (int) (p.getStat(Stat.HP) - p.getHP())).turns(2);
        p.addEffect(e1);
    }
    @Override
    protected String describe(){
        return "uses Rest";
    }
}
