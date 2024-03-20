/* File generated by the BNF Converter (bnfc 2.9.5). */

#ifndef ACTION_BUILDER_MFPG_H
#define ACTION_BUILDER_MFPG_H
/* You might want to change the above name. */

#include "Absyn.H"
#include "IString.h"
#include "NoteEnums.h"
#include "PhysAttrMap.h"
#include "Action.h"
#include "Action.cpp"
#include <vector>
#include <functional>
#include <utility>

template class Action<int>;
template class Action<double>;

class ActionBuilder : public Visitor
{
public:
	typedef int (distfun_int) (PhysAttrMap, PhysAttrMap);
	typedef double (distfun_dub) (PhysAttrMap, PhysAttrMap);
	typedef bool (condfun) (PhysAttrMap, PhysAttrMap);

	typedef ExValContainer (exp_fun) (const ExValContainer&, const ExValContainer&);

	typedef int (int_link) (int, const ExValContainer&);
	typedef double (dub_link) (double, const ExValContainer&);
	
	typedef bool (int_fun) (int, int);
	typedef bool (dub_fun) (double, double);

//----------- Output ------------------------//
	char output;

//----------- Attr exclusives ---------------//
	std::string attrtypes = "";
	std::vector<std::string> attrs;

//----------- String exclusives -------------//
	std::vector<IString> strings;
	noteenums::Note note;
	
//---------- Action exclusives -------------//
	std::vector<Action<int>> int_acts;
	std::vector<Action<double>> dub_acts;

	std::function<exp_fun> e_fun;

	std::function<int_link> i_link;
	std::function<dub_link> d_link;
	
	std::function<int_fun> i_fun;
	std::function<dub_fun> d_fun;

//----------- Action Dependencies ----------//
	std::vector<std::tuple<std::string, std::string, bool>> deps;

//----------- General ----------------------//
	int integer;
	char character;
	double dub;
	bool boolean;
	std::string str;


  void visitInput(Input *p);
  void visitOutput(Output *p);
  void visitAttrDecl(AttrDecl *p);
  void visitIStr(IStr *p);
  void visitSPos(SPos *p);
  void visitNoteDef(NoteDef *p);
  void visitNoteDefBase(NoteDefBase *p);
  void visitAttrType(AttrType *p);
  void visitAct(Act *p);
  void visitActionName(ActionName *p);
  void visitDFun(DFun *p);
  void visitCFun(CFun *p);
  void visitAttr(Attr *p);
  void visitCompOp(CompOp *p);
  void visitBoolOp(BoolOp *p);
  void visitNum(Num *p);
  void visitExp(Exp *p);
  void visitScale(Scale *p);
  void visitBool(Bool *p);
  void visitBInput(BInput *p);
  void visitDOutput(DOutput *p);
  void visitIOutput(IOutput *p);
  void visitDAttr(DAttr *p);
  void visitStringDef(StringDef *p);
  void visitISPos(ISPos *p);
  void visitINote(INote *p);
  void visitNNote(NNote *p);
  void visitNoteDefBase_A(NoteDefBase_A *p);
  void visitNoteDefBase_As(NoteDefBase_As *p);
  void visitNoteDefBase_B(NoteDefBase_B *p);
  void visitNoteDefBase_C(NoteDefBase_C *p);
  void visitNoteDefBase_Cs(NoteDefBase_Cs *p);
  void visitNoteDefBase_D(NoteDefBase_D *p);
  void visitNoteDefBase_Ds(NoteDefBase_Ds *p);
  void visitNoteDefBase_E(NoteDefBase_E *p);
  void visitNoteDefBase_F(NoteDefBase_F *p);
  void visitNoteDefBase_Fs(NoteDefBase_Fs *p);
  void visitNoteDefBase_G(NoteDefBase_G *p);
  void visitNoteDefBase_Gs(NoteDefBase_Gs *p);
  void visitAttrType_i(AttrType_i *p);
  void visitAttrType_d(AttrType_d *p);
  void visitAttrType_b(AttrType_b *p);
  void visitFunList(FunList *p);
  void visitAName(AName *p);
  void visitCombDist(CombDist *p);
  void visitScaledDist(ScaledDist *p);
  void visitDirectDist(DirectDist *p);
  void visitConstDist(ConstDist *p);
  void visitCombCond(CombCond *p);
  void visitCompCond(CompCond *p);
  void visitValueCond(ValueCond *p);
  void visitBoolCond(BoolCond *p);
  void visitAttrCond(AttrCond *p);
  void visitEAttr(EAttr *p);
  void visitEq(Eq *p);
  void visitNEq(NEq *p);
  void visitGt(Gt *p);
  void visitLt(Lt *p);
  void visitGte(Gte *p);
  void visitLte(Lte *p);
  void visitAnd(And *p);
  void visitOr(Or *p);
  void visitCInt(CInt *p);
  void visitCDouble(CDouble *p);
  void visitESub(ESub *p);
  void visitEPlus(EPlus *p);
  void visitSMul(SMul *p);
  void visitVTrue(VTrue *p);
  void visitVFalse(VFalse *p);
  void visitListAttrDecl(ListAttrDecl *p);
  void visitListIStr(ListIStr *p);
  void visitListAct(ListAct *p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

};


#endif
