package added.moves;
import ru.ifmo.se.pokemon.*;
public class LavaPlume extends SpecialMove{
    public LavaPlume(){
        super(Type.FIRE, 80, 100);
    }
    @Override
    protected void applyOppEffects(Pokemon p){
        Effect e = new Effect().condition(Status.BURN).chance(0.3);
        p.addEffect(e);
    }
    @Override
    protected String describe(){
        return "uses Lava Plume";
    }
}
