package added.moves;
import ru.ifmo.se.pokemon.*;
public class Flamethrower extends SpecialMove{
    public Flamethrower(){
        super(Type.FIRE, 90, 100);
    }
    @Override
    protected void applyOppEffects(Pokemon p){
        Effect e = new Effect().condition(Status.BURN).chance(0.1);
        p.addEffect(e);
    }
    @Override
    protected String describe(){
        return "uses Flamethrower";
    }
}
