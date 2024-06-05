/* File generated by the BNF Converter (bnfc 2.9.5). */

#ifndef INSTRUMENT_BUILDER_MFPG_H
#define INSTRUMENT_BUILDER_MFPG_H

#include "Absyn.H"
#include "IString.h"
#include "NoteEnums.h"
#include "NoteAttributes.h"
#include "Action.h"
#include "ActionSet.h"
#include "Instrument.h"

#include <vector>
#include <functional>
#include <utility>

class InstrumentBuilder : public Visitor {
public:
//----------- Typedefs for lambda functions //
	typedef int (distfun_int) (NoteAttributes, NoteAttributes);
	typedef double (distfun_dub) (NoteAttributes, NoteAttributes);
	typedef bool (condfun) (NoteAttributes, NoteAttributes);

	typedef ExValContainer (exp_fun) (const ExValContainer&, const ExValContainer&);

	typedef int (int_link) (int, const ExValContainer&);
	typedef double (dub_link) (double, const ExValContainer&);
	
	typedef bool (int_fun) (int, int);
	typedef bool (dub_fun) (double, double);
	
//----------- Instrument Outputs -----------//
	std::shared_ptr<Instrument<int>> i_inst;
	std::shared_ptr<Instrument<double>> d_inst;

	std::shared_ptr<ActionSet<int>> int_set;
	std::shared_ptr<ActionSet<double>> dub_set;

//----------- Output -----------------------//
	char output;

//----------- Attr exclusives --------------//
	std::string attrtypes = "";
	std::vector<std::string> attrs;

//----------- String exclusives ------------//
	std::vector<IString> strings;
	noteenums::Note note;
	noteenums::Duration duration;
	
//---------- Action exclusives -------------//
	Action<int> a_int;
	Action<double> a_dub;

	std::function<exp_fun> e_fun;

	std::function<int_link> i_link;
	std::function<dub_link> d_link;
	
	std::function<int_fun> i_fun;
	std::function<dub_fun> d_fun;

	ACCUMULATOR acc;
//----------- General ----------------------//
	int integer;
	char character;
	double dub;
	bool boolean;
	std::string str;

//----------- Parser functions -----------//
	void visitInput(Input *p);
	void visitOutput(Output *p);
	void visitAttrDecl(AttrDecl *p);
	void visitIStr(IStr *p);
	void visitSPos(SPos *p);
	void visitNoteDef(NoteDef *p);
	void visitNoteDefBase(NoteDefBase *p);
	void visitAttrType(AttrType *p);
  	void visitDurationDefBase(DurationDefBase *p);
	void visitAct(Act *p);
	void visitActionName(ActionName *p);
	void visitDep(Dep *p);
	void visitDFun(DFun *p);
	void visitCFun(CFun *p);
	void visitAttr(Attr *p);
	void visitCompOp(CompOp *p);
	void visitBoolOp(BoolOp *p);
	void visitNum(Num *p);
	void visitCNoteDef(CNoteDef *p);
	void visitCDurationDef(CDurationDef *p);
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
	void visitDurationDefBase_Double(DurationDefBase_Double *p);
	void visitDurationDefBase_Whole(DurationDefBase_Whole *p);
	void visitDurationDefBase_Half(DurationDefBase_Half *p);
	void visitDurationDefBase_Quarter(DurationDefBase_Quarter *p);
	void visitDurationDefBase_Eighth(DurationDefBase_Eighth *p);
	void visitDurationDefBase_Sixteenth(DurationDefBase_Sixteenth *p);
	void visitDurationDefBase_ThirtySecond(DurationDefBase_ThirtySecond *p);
	void visitDurationDefBase_SixtyFourth(DurationDefBase_SixtyFourth *p);
	void visitFunList(FunList *p);
	void visitAName(AName *p);
	void visitADeps(ADeps *p);
	void visitCombDist(CombDist *p);
	void visitScaledDist(ScaledDist *p);
	void visitDirectDist(DirectDist *p);
	void visitConstDist(ConstDist *p);
	void visitCombCond(CombCond *p);
	void visitCompCond(CompCond *p);
	void visitFrValueCond(FrValueCond *p);
	void visitToValueCond(ToValueCond *p);
	void visitBoolCond(BoolCond *p);
	void visitFrAttrCond(FrAttrCond *p);
	void visitToAttrCond(ToAttrCond *p);
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
	void visitCNote(CNote *p);
	void visitCDuration(CDuration *p);
	void visitCNNote(CNNote *p);
	void visitCNDuration(CNDuration *p);
	void visitESub(ESub *p);
	void visitEPlus(EPlus *p);
	void visitSMul(SMul *p);
	void visitVTrue(VTrue *p);
	void visitVFalse(VFalse *p);
	void visitListAttrDecl(ListAttrDecl *p);
	void visitListIStr(ListIStr *p);
	void visitListAct(ListAct *p);
	void visitListDep(ListDep *p);

	void visitInteger(Integer x);
	void visitChar(Char x);
	void visitDouble(Double x);
	void visitString(String x);
	void visitIdent(Ident x);
	void visitIdentifier(Identifier x);
};
#endif
