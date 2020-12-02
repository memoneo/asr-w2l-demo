
#ifndef CRUD_W2LSERVICE_HPP
#define CRUD_W2LSERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "w2l.hpp"

class W2lService {
private:
  OATPP_COMPONENT(std::shared_ptr<w2l::inputfiles::W2lHelper>, m_w2lHelper); // Inject database component
public:
  void transcribe(const std::string fileName);
};

#endif //CRUD_W2LSERVICE_HPP