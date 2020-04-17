open ApolloHooks

module GetExchangeRates = [%graphql {|
  query getExchangeRates {
    rates(currency: "USD") {
      currency
      rate
    }
  }
|}];


[@react.component]
let make = () => {
  let (simple, _full) = useQuery(GetExchangeRates.definition);


  <div>
  {
    switch(simple) {
      | Loading => <p>{React.string("Loading...")}</p>
      | Data(data) =>
        Js.log(data);
        <div>
          {React.string("cool")}
          (
            React.array(Array.of_list(
              List.map((item) => <p>{React.string(item.rate)}</p>, data##rates)
            ))
          )
        </div>
      | NoData
      | Error(_) => <p>{React.string("Get off my lawn!")}</p>
    }
  }
  </div>
}