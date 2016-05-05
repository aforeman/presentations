
#include <iostream>
#include "SWIGRubyRuntime.hxx"

extern "C" {
  // needed to provide the signature for initing our own module
  // this needs to match the signature of the module generated by SWIG
  void Init_EmbeddedScripting(void);
}

static VALUE evaluateSimpleImpl(VALUE arg) 
{
  return rb_eval_string(StringValuePtr(arg));
}

void evalString(const std::string &t_str)
{

  VALUE val = rb_str_new2(t_str.c_str());
  int error;

  rb_protect(evaluateSimpleImpl,val,&error);

  if (error != 0)
  {
    VALUE errval = rb_eval_string("$!.to_s");
    char *str = StringValuePtr(errval);
    std::string err(str);

    VALUE locval = rb_eval_string("$@.to_s");
    str = StringValuePtr(locval);
    std::string loc(str);

    throw std::runtime_error("Ruby Error: " + err + " at: " + loc);
  } 
}

int main(int argc, char *argv[])
{
  ruby_sysinit(&argc, &argv);
  {
    RUBY_INIT_STACK;
    ruby_init();
  }

  Init_EmbeddedScripting();

  evalString(R"ruby(1000000.times { puts(EmbeddedScripting::hello('world')) })ruby");

}


