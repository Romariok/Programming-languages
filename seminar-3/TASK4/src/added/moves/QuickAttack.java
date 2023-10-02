package added.moves;
import ru.ifmo.se.pokemon.*;
public class QuickAttack extends PhysicalMove{
    public QuickAttack(){
        super(Type.NORMAL, 40, 100, 1, 10);
    }
    @Override
    protected String describe(){
        return "uses Quick Attack";
    }
}
